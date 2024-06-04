//
// Created by lucac on 27/05/2024.
//

#include "Renderer.h"
#include "Miscellaneous/Assert.h"
#include "imgui/imgui_impl_sdlgpu.h"

namespace kc {
    Renderer::Renderer(SDL_Window *window,
                       SDL_GpuBackendBits backend,
                       SDL_GpuSwapchainComposition composition,
                       SDL_GpuSampleCount MSAA,
                       SDL_GpuPresentMode presentMode,
                       bool useImgui) : m_pWindow(window), m_swapchainComposition(composition),m_sampleCount(MSAA), m_presentMode(presentMode), m_bImguiEnabled(useImgui) {

        m_pDevice = SDL_GpuCreateDevice(backend, g_bDebug);
        ASSERT(m_pDevice != nullptr, "Failed to create GPU Device, aborting application");

        if (presentMode == SDL_GPU_PRESENTMODE_MAILBOX && !SDL_GpuSupportsPresentMode(m_pDevice, m_pWindow, SDL_GPU_PRESENTMODE_MAILBOX)) {
            m_presentMode = SDL_GPU_PRESENTMODE_VSYNC;
        }

        bool res = SDL_GpuClaimWindow(m_pDevice, m_pWindow, m_swapchainComposition, m_presentMode);
        ASSERT(res,"Failed to claim SDL Window, aborting application");

        m_HDRMainRTCreateInfo.isCube = false;
        m_HDRMainRTCreateInfo.depth = 1;
        m_HDRMainRTCreateInfo.width = 1;
        m_HDRMainRTCreateInfo.height = 1;
        m_HDRMainRTCreateInfo.layerCount = 1;
        m_HDRMainRTCreateInfo.levelCount = 1;
        m_HDRMainRTCreateInfo.sampleCount = SDL_GPU_SAMPLECOUNT_1;
        m_HDRMainRTCreateInfo.format = SDL_GPU_TEXTUREFORMAT_R16G16B16A16;
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
            clearPassAttachmentInfo.textureSlice.texture = m_pHDRMainRenderTarget;
            clearPassAttachmentInfo.textureSlice.mipLevel = 0;
            clearPassAttachmentInfo.textureSlice.layer = 0;
            clearPassAttachmentInfo.cycle = SDL_TRUE;

            //Clear pass, aka I clear the main render target before drawing anything else
            SDL_GpuRenderPass *clearRenderPass = SDL_GpuBeginRenderPass(m_pMainCommandBuffer, &clearPassAttachmentInfo,1, {});
            SDL_GpuEndRenderPass(clearRenderPass);

        }
    }

    void Renderer::EndDraw() {
        if (m_pSwapchainTexture) {
            SDL_GpuTextureRegion RTRegion = {};
            RTRegion.w = m_curSwapchainWidth;
            RTRegion.h = m_curSwapchainHeight;
            RTRegion.d = 1;
            RTRegion.textureSlice.layer = 0;
            RTRegion.textureSlice.mipLevel = 0;
            RTRegion.textureSlice.texture = m_pHDRMainRenderTarget;

            SDL_GpuTextureRegion SwapchainRegion = {};
            SwapchainRegion.w = m_curSwapchainWidth;
            SwapchainRegion.h = m_curSwapchainHeight;
            SwapchainRegion.d = 1;
            SwapchainRegion.textureSlice.layer = 0;
            SwapchainRegion.textureSlice.mipLevel = 0;
            SwapchainRegion.textureSlice.texture = m_pSwapchainTexture;

            //Finally I blit the RT to the swapchain texture I acquired earlier
            SDL_GpuBlit(m_pMainCommandBuffer, &RTRegion, &SwapchainRegion, SDL_GPU_FILTER_LINEAR,SDL_TRUE);

            //Render ImGui to the SDR swapchain texture if enabled
            if(m_bImguiEnabled){
                SDL_GpuColorAttachmentInfo swapchainAttachmentInfo = {};
                swapchainAttachmentInfo.loadOp = SDL_GPU_LOADOP_LOAD;
                swapchainAttachmentInfo.storeOp = SDL_GPU_STOREOP_STORE;
                swapchainAttachmentInfo.textureSlice.texture = m_pSwapchainTexture;
                swapchainAttachmentInfo.textureSlice.mipLevel = 0;
                swapchainAttachmentInfo.textureSlice.layer = 0;
                swapchainAttachmentInfo.cycle = SDL_TRUE;
                SDL_GpuRenderPass *imguiRenderPass = SDL_GpuBeginRenderPass(m_pMainCommandBuffer,&swapchainAttachmentInfo, 1, {});
                    ImGui_ImplSDLGpu_RenderDrawData(ImGui::GetDrawData(),imguiRenderPass);
                SDL_GpuEndRenderPass(imguiRenderPass);
            }
        }
        SDL_GpuSubmit(m_pMainCommandBuffer);
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
            INFO("The swapchain changed size: {0}, {1}",m_curSwapchainWidth,m_curSwapchainHeight);
        }
    }

    void Renderer::SetClearColor(const SDL_GpuColor clearColor) {
        m_clearColor = clearColor;
    }

    void Renderer::Clean() {
        SDL_GpuWait(m_pDevice);
        SDL_GpuUnclaimWindow(m_pDevice, m_pWindow);
        SDL_GpuReleaseTexture(m_pDevice, m_pHDRMainRenderTarget);
        SDL_GpuDestroyDevice(m_pDevice);
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
}
