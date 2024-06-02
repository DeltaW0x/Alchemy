//
// Created by lucac on 27/05/2024.
//

#include "Renderer.h"

namespace kc
{
    Renderer::Renderer(SDL_Window *window,
                       SDL_GpuBackendBits backend,
                       SDL_GpuSwapchainComposition composition,
                       SDL_GpuSampleCount MSAA) : m_pWindow(window), m_swapchainComposition(composition), m_sampleCount(MSAA)
    {

        m_pDevice = SDL_GpuCreateDevice(backend, g_bDebug);
        
        if (SDL_GpuSupportsPresentMode(m_pDevice, m_pWindow, SDL_GPU_PRESENTMODE_MAILBOX))
        {
            SDL_GpuClaimWindow(m_pDevice, m_pWindow, m_swapchainComposition, SDL_GPU_PRESENTMODE_MAILBOX);
            printf("Using mailbox \n");
            m_presentMode = SDL_GPU_PRESENTMODE_MAILBOX;
        }
        else
        {
            SDL_GpuClaimWindow(m_pDevice, m_pWindow, m_swapchainComposition, SDL_GPU_PRESENTMODE_VSYNC);
            printf("Using vsync \n");
            m_presentMode = SDL_GPU_PRESENTMODE_VSYNC;
        }

    }

    void Renderer::BeginDraw()
    {

    }

    void Renderer::EndDraw()
    {
      
    }

    void Renderer::CheckIfSwapchainChanged()
    {
        
    }

    void Renderer::Clean()
    {
        SDL_GpuWait(m_pDevice);
        SDL_GpuUnclaimWindow(m_pDevice, m_pWindow);
        SDL_GpuDestroyDevice(m_pDevice);
    }
}
