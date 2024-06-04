//
// Created by lucac on 04/06/2024.
//

#include "EditorRenderer.h"
#include "../Context/EditorContext.h"

EditorRenderer::EditorRenderer(EditorContext *context) : m_pCtx(context) {
    m_pLowLevelRenderer = new Renderer(context->GetWindow(), SDL_GPU_BACKEND_VULKAN, SDL_GPU_SWAPCHAINCOMPOSITION_SDR,
                                       SDL_GPU_SAMPLECOUNT_1,
                                       SDL_GPU_PRESENTMODE_VSYNC);

    m_pHdrRenderTargetInfo.isCube = false;
    m_pHdrRenderTargetInfo.depth = 1;
    m_pHdrRenderTargetInfo.width = 100;
    m_pHdrRenderTargetInfo.height = 100;
    m_pHdrRenderTargetInfo.layerCount = 1;
    m_pHdrRenderTargetInfo.levelCount = 1;
    m_pHdrRenderTargetInfo.sampleCount = SDL_GPU_SAMPLECOUNT_1;
    m_pHdrRenderTargetInfo.format = SDL_GPU_TEXTUREFORMAT_R8G8B8A8;
    m_pHdrRenderTargetInfo.usageFlags = SDL_GPU_TEXTUREUSAGE_SAMPLER_BIT | SDL_GPU_TEXTUREUSAGE_COLOR_TARGET_BIT;
    m_pHdrRenderTarget = SDL_GpuCreateTexture(m_pLowLevelRenderer->GetDevice(), &m_pHdrRenderTargetInfo);

    m_pSdrRenderTargetInfo.isCube = false;
    m_pSdrRenderTargetInfo.depth = 1;
    m_pSdrRenderTargetInfo.width = 100;
    m_pSdrRenderTargetInfo.height = 100;
    m_pSdrRenderTargetInfo.layerCount = 1;
    m_pSdrRenderTargetInfo.levelCount = 1;
    m_pSdrRenderTargetInfo.sampleCount = SDL_GPU_SAMPLECOUNT_1;
    m_pSdrRenderTargetInfo.format = SDL_GPU_TEXTUREFORMAT_R8G8B8A8;
    m_pSdrRenderTargetInfo.usageFlags = SDL_GPU_TEXTUREUSAGE_SAMPLER_BIT | SDL_GPU_TEXTUREUSAGE_COLOR_TARGET_BIT;
    m_pSdrRenderTarget = SDL_GpuCreateTexture(m_pLowLevelRenderer->GetDevice(), &m_pSdrRenderTargetInfo);

    SDL_GpuSamplerCreateInfo samplerInfo = {};
    samplerInfo.minFilter = SDL_GPU_FILTER_LINEAR;
    samplerInfo.magFilter = SDL_GPU_FILTER_LINEAR;
    samplerInfo.mipmapMode = SDL_GPU_SAMPLERMIPMAPMODE_LINEAR;
    samplerInfo.addressModeU = SDL_GPU_SAMPLERADDRESSMODE_CLAMP_TO_EDGE;
    samplerInfo.addressModeV = SDL_GPU_SAMPLERADDRESSMODE_CLAMP_TO_EDGE;
    samplerInfo.addressModeW = SDL_GPU_SAMPLERADDRESSMODE_CLAMP_TO_EDGE;
    samplerInfo.mipLodBias = 0.0f;
    samplerInfo.anisotropyEnable = SDL_FALSE;
    samplerInfo.compareEnable = SDL_FALSE;
    samplerInfo.minLod = 0.0f;
    samplerInfo.maxLod = 1.0f;
    m_pViewportTextureSampler = SDL_GpuCreateSampler(m_pLowLevelRenderer->GetDevice(), &samplerInfo);
}

EditorRenderer::~EditorRenderer() {
    SDL_GpuWait(m_pLowLevelRenderer->GetDevice());
    SDL_GpuReleaseSampler(m_pLowLevelRenderer->GetDevice(), m_pViewportTextureSampler);
    SDL_GpuReleaseTexture(m_pLowLevelRenderer->GetDevice(), m_pHdrRenderTarget);
    SDL_GpuReleaseTexture(m_pLowLevelRenderer->GetDevice(), m_pSdrRenderTarget);
    delete m_pLowLevelRenderer;
}

void EditorRenderer::BeginDraw() {
    m_pLowLevelRenderer->BeginDraw();
    m_pMainCmdBuffer = SDL_GpuAcquireCommandBuffer(m_pLowLevelRenderer->GetDevice());
    if (m_pCtx->GetUILayer()->GetViewport()->ViewportSizeChanged(&m_currentViewportSize)) {
        SDL_GpuReleaseTexture(m_pLowLevelRenderer->GetDevice(), m_pHdrRenderTarget);
        SDL_GpuReleaseTexture(m_pLowLevelRenderer->GetDevice(), m_pSdrRenderTarget);
        m_pHdrRenderTargetInfo.width = (u32) m_currentViewportSize.x;
        m_pHdrRenderTargetInfo.height = (u32) m_currentViewportSize.y;
        m_pSdrRenderTargetInfo.width = (u32) m_currentViewportSize.x;
        m_pSdrRenderTargetInfo.height = (u32) m_currentViewportSize.y;

        m_pHdrRenderTarget = SDL_GpuCreateTexture(m_pLowLevelRenderer->GetDevice(), &m_pHdrRenderTargetInfo);
        m_pSdrRenderTarget = SDL_GpuCreateTexture(m_pLowLevelRenderer->GetDevice(), &m_pSdrRenderTargetInfo);
    }

    SDL_GpuColorAttachmentInfo hdrAttachmentInfoClear = {};
    hdrAttachmentInfoClear.loadOp = SDL_GPU_LOADOP_CLEAR;
    hdrAttachmentInfoClear.storeOp = SDL_GPU_STOREOP_STORE;
    hdrAttachmentInfoClear.clearColor = {0, 0, 0, 1};
    hdrAttachmentInfoClear.cycle = SDL_TRUE;
    hdrAttachmentInfoClear.textureSlice.texture = m_pHdrRenderTarget;

    SDL_GpuRenderPass *clearPass = SDL_GpuBeginRenderPass(m_pMainCmdBuffer, &hdrAttachmentInfoClear, 1, {});
    SDL_GpuEndRenderPass(clearPass);

    SDL_GpuTextureRegion hdrTexRegion = {};
    hdrTexRegion.w = m_currentViewportSize.x;
    hdrTexRegion.h = m_currentViewportSize.y;
    hdrTexRegion.d = 1;
    hdrTexRegion.textureSlice.texture = m_pHdrRenderTarget;

    SDL_GpuTextureRegion sdrTexRegion = {};
    sdrTexRegion.w = m_currentViewportSize.x;
    sdrTexRegion.h = m_currentViewportSize.y;
    sdrTexRegion.d = 1;
    sdrTexRegion.textureSlice.texture = m_pSdrRenderTarget;

    SDL_GpuBlit(m_pMainCmdBuffer, &hdrTexRegion, &sdrTexRegion, SDL_GPU_FILTER_LINEAR,SDL_TRUE);
    SDL_GpuSubmit(m_pMainCmdBuffer);
}

void EditorRenderer::DrawUI() {
    ImGui_ImplSDLGpu_NewFrame();
    ImGui_ImplSDL3_NewFrame();
    ImGui::NewFrame();
    ImGui::DockSpaceOverViewport();
    m_binding = {m_pSdrRenderTarget, m_pViewportTextureSampler};
    m_pCtx->GetUILayer()->GetViewport()->Render(&m_binding);
    m_pCtx->GetUILayer()->GetManager()->RenderAllElements();
    ImGui::Render();

    SDL_GpuColorAttachmentInfo swapchainAttachmentInfo = {};
    swapchainAttachmentInfo.loadOp = SDL_GPU_LOADOP_LOAD;
    swapchainAttachmentInfo.storeOp = SDL_GPU_STOREOP_STORE;
    swapchainAttachmentInfo.textureSlice.texture = m_pLowLevelRenderer->GetSwapchainTexture();
    swapchainAttachmentInfo.textureSlice.mipLevel = 0;
    swapchainAttachmentInfo.textureSlice.layer = 0;
    swapchainAttachmentInfo.cycle = SDL_TRUE;

    SDL_GpuRenderPass *imguiRenderPass = SDL_GpuBeginRenderPass(m_pLowLevelRenderer->GetMainCommandBuffer(),
                                                                &swapchainAttachmentInfo, 1, {});
    ImGui_ImplSDLGpu_RenderDrawData(ImGui::GetDrawData(), imguiRenderPass);
    SDL_GpuEndRenderPass(imguiRenderPass);
}

void EditorRenderer::EndDraw() {
    DrawUI();
    m_pLowLevelRenderer->EndDraw();
    ImGuiIO &io = ImGui::GetIO();
    if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable) {
        ImGui::UpdatePlatformWindows();
        ImGui::RenderPlatformWindowsDefault();
    }
}

Renderer *EditorRenderer::GetLowLevelRenderer() {
    return m_pLowLevelRenderer;
}
