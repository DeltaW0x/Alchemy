//
// Created by lucac on 27/05/2024.
//

#ifndef RENDERER_H
#define RENDERER_H
#include <SDL3/SDL.h>
#include "Miscellaneous/Types.h"

namespace kc {
    class Renderer {
    public:
        Renderer(SDL_Window *window, SDL_GpuBackendBits backend, SDL_GpuSwapchainComposition composition,
                 SDL_GpuSampleCount MSAA, SDL_GpuPresentMode presentMode, bool useImgui);

        void InitStructures();

        void BeginDraw();
        void EndDraw();

        void CheckSwapchainSize();
        void SetClearColor(SDL_GpuColor clearColor);
        void Clean();

        [[nodiscard]] SDL_GpuDevice *GetDevice() const;
        [[nodiscard]] SDL_GpuPresentMode GetPresentMode() const;
        [[nodiscard]] SDL_GpuSwapchainComposition GetSwapchainComposition() const;
        [[nodiscard]] SDL_GpuColorAttachmentInfo GetRenderTargetAttachmentInfo() const;
        SDL_GpuColorAttachmentInfo m_MainRTAttachmentInfo = {};
    private:
        SDL_GpuDevice *m_pDevice = nullptr;
        SDL_Window *m_pWindow = nullptr;

        SDL_GpuTexture* m_pSwapchainTexture = nullptr;
        SDL_GpuTexture* m_pHDRMainRenderTarget = nullptr;

        SDL_GpuTextureCreateInfo m_HDRMainRTCreateInfo = {};


        SDL_GpuCommandBuffer* m_pMainCommandBuffer = nullptr;

        SDL_GpuBackend m_choosenBackend;
        SDL_GpuPresentMode m_presentMode;
        SDL_GpuSwapchainComposition m_swapchainComposition;
        SDL_GpuSampleCount m_sampleCount;
        SDL_GpuColor m_clearColor = {0,0,0,1};

        u32 m_prevSwpachainWidth  = 0;
        u32 m_prevSwapchainHeight = 0;
        u32 m_curSwapchainWidth  = 0;
        u32 m_curSwapchainHeight = 0;

        bool m_bImguiEnabled = false;
    };
}
#endif // RENDERER_H
