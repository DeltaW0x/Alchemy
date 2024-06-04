//
// Created by lucac on 27/05/2024.
//

#include "Renderer.h"
#include "Miscellaneous/Assert.h"
#include "imgui/imgui_impl_sdlgpu.h"

Renderer::Renderer(SDL_Window *window,
                   SDL_GpuBackendBits backend,
                   SDL_GpuSwapchainComposition composition,
                   SDL_GpuSampleCount MSAA,
                   SDL_GpuPresentMode presentMode) : m_pWindow(window), m_swapchainComposition(composition),
                                                     m_sampleCount(MSAA),
                                                     m_presentMode(presentMode) {
    m_pDevice = SDL_GpuCreateDevice(backend, g_bDebug);
    ASSERT(m_pDevice != nullptr, "Failed to create GPU Device, aborting application");

    if (presentMode == SDL_GPU_PRESENTMODE_MAILBOX && !SDL_GpuSupportsPresentMode(
            m_pDevice, m_pWindow, SDL_GPU_PRESENTMODE_MAILBOX)) {
        m_presentMode = SDL_GPU_PRESENTMODE_VSYNC;
    }

    bool res = SDL_GpuClaimWindow(m_pDevice, m_pWindow, m_swapchainComposition, m_presentMode);
    ASSERT(res, "Failed to claim SDL Window, aborting application");

    m_HDRMainRTCreateInfo.isCube = false;
    m_HDRMainRTCreateInfo.depth = 1;
    m_HDRMainRTCreateInfo.width = 1;
    m_HDRMainRTCreateInfo.height = 1;
    m_HDRMainRTCreateInfo.layerCount = 1;
    m_HDRMainRTCreateInfo.levelCount = 1;
    m_HDRMainRTCreateInfo.sampleCount = SDL_GPU_SAMPLECOUNT_1;
    m_HDRMainRTCreateInfo.format = SDL_GPU_TEXTUREFORMAT_R8G8B8A8;
    m_HDRMainRTCreateInfo.usageFlags = SDL_GPU_TEXTUREUSAGE_SAMPLER_BIT | SDL_GPU_TEXTUREUSAGE_COLOR_TARGET_BIT;
    m_pHDRMainRenderTarget = SDL_GpuCreateTexture(m_pDevice, &m_HDRMainRTCreateInfo);
    ASSERT(m_pHDRMainRenderTarget != nullptr, "Failed to create backbuffer texture, aborting application");


    m_MainRTAttachmentInfo.loadOp = SDL_GPU_LOADOP_LOAD;
    m_MainRTAttachmentInfo.storeOp = SDL_GPU_STOREOP_STORE;
    m_MainRTAttachmentInfo.textureSlice.texture = m_pHDRMainRenderTarget;
    m_MainRTAttachmentInfo.textureSlice.mipLevel = 0;
    m_MainRTAttachmentInfo.textureSlice.layer = 0;
    m_MainRTAttachmentInfo.cycle = SDL_TRUE;
}

Renderer::~Renderer() {
    SDL_GpuWait(m_pDevice);
    SDL_GpuUnclaimWindow(m_pDevice, m_pWindow);
    SDL_GpuReleaseTexture(m_pDevice, m_pHDRMainRenderTarget);
    SDL_GpuDestroyDevice(m_pDevice);
}

void Renderer::BeginDraw() {
    m_pMainCommandBuffer = SDL_GpuAcquireCommandBuffer(m_pDevice);
    m_pSwapchainTexture = SDL_GpuAcquireSwapchainTexture(m_pMainCommandBuffer, m_pWindow, &m_curSwapchainWidth,
                                                         &m_curSwapchainHeight);
    if (m_pSwapchainTexture) {
        CheckSwapchainSize();
        SDL_GpuColorAttachmentInfo clearPassAttachmentInfo = {};
        clearPassAttachmentInfo.loadOp = SDL_GPU_LOADOP_CLEAR;
        clearPassAttachmentInfo.storeOp = SDL_GPU_STOREOP_STORE;
        clearPassAttachmentInfo.clearColor = m_clearColor;
        clearPassAttachmentInfo.textureSlice.texture = m_pSwapchainTexture;
        clearPassAttachmentInfo.textureSlice.mipLevel = 0;
        clearPassAttachmentInfo.textureSlice.layer = 0;
        clearPassAttachmentInfo.cycle = SDL_TRUE;

        //Clear pass, aka I clear the main render target before drawing anything else
        SDL_GpuRenderPass *clearRenderPass = SDL_GpuBeginRenderPass(m_pMainCommandBuffer, &clearPassAttachmentInfo, 1,{});
        SDL_GpuEndRenderPass(clearRenderPass);
    }
}

void Renderer::EndDraw() {
    if (m_pSwapchainTexture) {
        SDL_GpuSubmit(m_pMainCommandBuffer);
    }
}


void Renderer::CheckSwapchainSize() {
    if (m_curSwapchainWidth != m_prevSwpachainWidth || m_curSwapchainHeight != m_prevSwapchainHeight) {
        SDL_GpuReleaseTexture(m_pDevice, m_pHDRMainRenderTarget);
        m_HDRMainRTCreateInfo.width = m_curSwapchainWidth;
        m_HDRMainRTCreateInfo.height = m_curSwapchainHeight;
        m_prevSwpachainWidth = m_curSwapchainWidth;
        m_prevSwapchainHeight = m_curSwapchainHeight;
        m_pHDRMainRenderTarget = SDL_GpuCreateTexture(m_pDevice, &m_HDRMainRTCreateInfo);

        m_MainRTAttachmentInfo.textureSlice.texture = m_pHDRMainRenderTarget;
        INFO("The swapchain changed size: {0}, {1}", m_curSwapchainWidth, m_curSwapchainHeight);
    }
}

void Renderer::SetClearColor(const SDL_GpuColor clearColor) {
    m_clearColor = clearColor;
}

SDL_GpuTexture *Renderer::GetSwapchainTexture() {
    return m_pSwapchainTexture;
}

SDL_GpuCommandBuffer * Renderer::GetMainCommandBuffer() {
    return m_pMainCommandBuffer;
}

SDL_GpuDevice *Renderer::GetDevice() const {
    return m_pDevice;
}

SDL_GpuPresentMode Renderer::GetPresentMode() const {
    return m_presentMode;
}

SDL_GpuSwapchainComposition Renderer::GetSwapchainComposition() const {
    return m_swapchainComposition;
}

SDL_GpuColorAttachmentInfo Renderer::GetRenderTargetAttachmentInfo() const {
    return m_MainRTAttachmentInfo;
}
