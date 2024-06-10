//
// Created by lucac on 09/06/2024.
//

#include "Renderer.h"
#include "Logging.h"


Renderer::Renderer(SDL_GpuDevice *device, SDL_Window *window)  :m_pGpuDevice(device),m_pMainWindow(window){

    m_renderTargetInfo.isCube = false;
    m_renderTargetInfo.width = 19;
    m_renderTargetInfo.height = 6;
    m_renderTargetInfo.depth = 1;
    m_renderTargetInfo.layerCount = 1;
    m_renderTargetInfo.levelCount = 1;
    m_renderTargetInfo.sampleCount = SDL_GPU_SAMPLECOUNT_1;
    m_renderTargetInfo.format = SDL_GPU_TEXTUREFORMAT_R16G16B16A16;
    m_renderTargetInfo.usageFlags = SDL_GPU_TEXTUREUSAGE_SAMPLER_BIT | SDL_GPU_TEXTUREUSAGE_COLOR_TARGET_BIT;

    m_pRenderTargetTexture = SDL_GpuCreateTexture(m_pGpuDevice,&m_renderTargetInfo);
    ASSERT(m_pRenderTargetTexture != NULL, "Failed to create render target texture");

    m_pUberVertexBuffer = SDL_GpuCreateBuffer(m_pGpuDevice,SDL_GPU_BUFFERUSAGE_VERTEX_BIT,1024 * 1024 * 128);//Alloc 128MB for vertexBuffer (if debug, otherwise find smaller size)
    m_pUberIndexBuffer = SDL_GpuCreateBuffer(m_pGpuDevice,SDL_GPU_BUFFERUSAGE_INDEX_BIT,1024 * 1024 * 128); //Alloc 128MB for indexBuffer (if debug, otherwise find smaller size)
}

void Renderer::Dispose() {
    SDL_GpuWait(m_pGpuDevice);
    SDL_GpuReleaseBuffer(m_pGpuDevice,m_pUberVertexBuffer);
    SDL_GpuReleaseBuffer(m_pGpuDevice,m_pUberIndexBuffer);
    SDL_GpuReleaseTexture(m_pGpuDevice,m_pRenderTargetTexture);
}

void Renderer::StartDraw() {
    m_pInternalCmd = SDL_GpuAcquireCommandBuffer(m_pGpuDevice);
    ASSERT(m_pInternalCmd != NULL, "Failed to acquire main command buffer");

    m_pSwapchainTexture = SDL_GpuAcquireSwapchainTexture(m_pInternalCmd, m_pMainWindow, &m_currentSwapchainWidth, &m_currentSwapchainHeight);

    if(m_pSwapchainTexture != NULL) {

        HandleSwapchainChange();

        SDL_GpuColorAttachmentInfo clearAttachmentInfo = {};
        clearAttachmentInfo.textureSlice.texture = m_pRenderTargetTexture;
        clearAttachmentInfo.clearColor = { 0.16f, 0.16f, 0.16f, 1.0f };
        clearAttachmentInfo.loadOp = SDL_GPU_LOADOP_CLEAR;
        clearAttachmentInfo.storeOp = SDL_GPU_STOREOP_STORE;
        clearAttachmentInfo.cycle = SDL_TRUE;

        SDL_GpuRenderPass* renderPass = SDL_GpuBeginRenderPass(m_pInternalCmd, &clearAttachmentInfo, 1, NULL);
        SDL_GpuEndRenderPass(renderPass);

    }
}

void Renderer::EndDraw() {
    if(m_pSwapchainTexture != NULL) {

        SDL_GpuTextureRegion swapchainBlitRegion = {};
        swapchainBlitRegion.w = m_currentSwapchainWidth;
        swapchainBlitRegion.h = m_currentSwapchainHeight;
        swapchainBlitRegion.d = 1;
        swapchainBlitRegion.textureSlice.layer = 0;
        swapchainBlitRegion.textureSlice.mipLevel = 0;
        swapchainBlitRegion.textureSlice.texture = m_pSwapchainTexture;

        SDL_GpuTextureRegion rtBlitRegion = {};
        rtBlitRegion.w = m_currentSwapchainWidth;
        rtBlitRegion.h = m_currentSwapchainHeight;
        rtBlitRegion.d = 1;
        rtBlitRegion.textureSlice.layer = 0;
        rtBlitRegion.textureSlice.mipLevel = 0;
        rtBlitRegion.textureSlice.texture = m_pRenderTargetTexture;

        SDL_GpuBlit(m_pInternalCmd,&rtBlitRegion,&swapchainBlitRegion,SDL_GPU_FILTER_LINEAR,SDL_TRUE);
    }
    SDL_GpuSubmit(m_pInternalCmd);
}

void Renderer::HandleSwapchainChange() {
    if(m_currentSwapchainWidth != m_previousSwapchainWidth || m_currentSwapchainHeight != m_previousSwapchainHeight) {
        m_previousSwapchainWidth = m_currentSwapchainWidth;
        m_previousSwapchainHeight = m_currentSwapchainHeight;

        SDL_GpuReleaseTexture(m_pGpuDevice,m_pRenderTargetTexture);
        m_renderTargetInfo.width = m_currentSwapchainWidth;
        m_renderTargetInfo.height = m_currentSwapchainHeight;
        m_pRenderTargetTexture = SDL_GpuCreateTexture(m_pGpuDevice,&m_renderTargetInfo);

        LOG_INFO("New swapchain size ({0},{1})",m_currentSwapchainWidth,m_currentSwapchainHeight);
    }
}

SDL_GpuTexture * Renderer::GetMainRT() {
    return m_pRenderTargetTexture;
}