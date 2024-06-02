//
// Created by lucac on 27/05/2024.
//

#ifndef RENDERER_H
#define RENDERER_H
#include <SDL3/SDL.h>
#include "../Miscellaneous/Types.h"

namespace kc
{
    class Renderer
    {
    public:
        Renderer()
        {
            
        }

        Renderer(SDL_Window *window, SDL_GpuBackendBits backend, SDL_GpuSwapchainComposition composition, SDL_GpuSampleCount MSAA);

        void BeginDraw();
        void EndDraw();

        void Clean();

        SDL_GpuDevice *GetDevice() const
        {
            return m_pDevice;
        }
        SDL_GpuPresentMode GetPresentMode() const
        {
            return m_presentMode;
        }
        SDL_GpuSwapchainComposition GetSwapchainComposition() const
        {
            return m_swapchainComposition;
        }
    private:
        void CheckIfSwapchainChanged();

    private:
        SDL_GpuDevice *m_pDevice = nullptr;
        SDL_Window *m_pWindow = nullptr;
        
        SDL_GpuBackend m_choosenBackend;
        SDL_GpuPresentMode m_presentMode;
        SDL_GpuSwapchainComposition m_swapchainComposition;
        SDL_GpuSampleCount m_sampleCount;
    };
}
#endif // RENDERER_H
