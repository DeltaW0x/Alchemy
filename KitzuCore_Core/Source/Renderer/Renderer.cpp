//
// Created by lucac on 27/05/2024.
//

#include "Renderer.h"

namespace kc {
    Renderer::Renderer(SDL_Window *window, SDL_GpuBackendBits backend, SDL_GpuSwapchainComposition composition,
                       SDL_GpuPresentMode presentmode) : m_pWindow(window) {
        m_pDevice = SDL_GpuCreateDevice(backend, g_bDebug);
        SDL_GpuClaimWindow(m_pDevice, m_pWindow, composition, presentmode);
    }

    void Renderer::StartDraw(SDL_GpuColor clearColor) {
        u32 width, height;

        m_pMainCommandBuffer = SDL_GpuAcquireCommandBuffer(m_pDevice);
        m_pBackbufferTexture = SDL_GpuAcquireSwapchainTexture(m_pMainCommandBuffer, m_pWindow, &width, &height);

        m_viewport.x = 0;
        m_viewport.y = 0;
        m_viewport.w = width;
        m_viewport.h = height;

        m_scissor.x = 0;
        m_scissor.y = 0;
        m_scissor.w = width;
        m_scissor.h = height;

        if (m_pBackbufferTexture != nullptr) {
            SDL_GpuColorAttachmentInfo colorAttachmentInfo = {};
            colorAttachmentInfo.textureSlice.texture = m_pBackbufferTexture;
            colorAttachmentInfo.clearColor = clearColor;
            colorAttachmentInfo.loadOp = SDL_GPU_LOADOP_CLEAR;
            colorAttachmentInfo.storeOp = SDL_GPU_STOREOP_STORE;

            m_pMainRenderPass = SDL_GpuBeginRenderPass(m_pMainCommandBuffer, &colorAttachmentInfo, 1, NULL);
        }
    }

    void Renderer::EndDraw() {
        if (m_pBackbufferTexture != nullptr) {
            SDL_GpuEndRenderPass(m_pMainRenderPass);
        }
        SDL_GpuSubmit(m_pMainCommandBuffer);
    }

    void Renderer::Clean() {
        SDL_GpuWait(m_pDevice);
        SDL_GpuUnclaimWindow(m_pDevice, m_pWindow);
        SDL_GpuDestroyDevice(m_pDevice);
    }
}
