//
// Created by lucac on 27/05/2024.
//

#ifndef RENDERER_H
#define RENDERER_H
#include <SDL3/SDL.h>
#include "../Miscellaneous/Types.h"

namespace kc {
    class Renderer {
    public:
        Renderer() {
        }

        Renderer(SDL_Window *window, SDL_GpuBackendBits backend, SDL_GpuSwapchainComposition composition,
                 SDL_GpuPresentMode presentmode);

        void StartDraw(SDL_GpuColor clearColor);

        void EndDraw();

        void Clean();

        SDL_GpuDevice* GetDevice() {
            return m_pDevice;
        }
        SDL_GpuRenderPass* GetMainRenderPass() {
            return m_pMainRenderPass;
        }
    private:
        SDL_GpuDevice *m_pDevice = nullptr;
        SDL_Window *m_pWindow = nullptr;
        SDL_GpuViewport m_viewport;
        SDL_GpuRect m_scissor;
        SDL_GpuBackend m_choosenBackend;
        SDL_GpuCommandBuffer *m_pMainCommandBuffer;
        SDL_GpuTexture *m_pBackbufferTexture;
        SDL_GpuRenderPass *m_pMainRenderPass;
        u32 m_backbufferWidth, m_backbufferHeight;
    };
}
#endif //RENDERER_H
