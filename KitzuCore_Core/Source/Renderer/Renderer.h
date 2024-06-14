//
// Created by lucac on 09/06/2024.
//

#ifndef RENDERER_H
#define RENDERER_H

#include <unordered_map>
#include <SDL3/SDL.h>
#include <vector>
class Renderer {
public:
    Renderer(SDL_GpuDevice* device,  SDL_Window* window,SDL_GpuSampleCount msaa);

    void Dispose();

    void StartDraw();
    void EndDraw();

    SDL_GpuTexture* GetMainRT();

private:
    void HandleSwapchainChange();
private:
    SDL_GpuTexture* m_pSwapchainTexture    = NULL;
    SDL_GpuTexture* m_pRenderTargetTexture = NULL;

    SDL_GpuDevice *m_pGpuDevice  = NULL;
    SDL_Window    *m_pMainWindow = NULL;

    SDL_GpuTextureCreateInfo m_renderTargetInfo = {};

    SDL_GpuCommandBuffer* m_pInternalCmd = NULL;

    uint32_t m_currentSwapchainWidth = 0,m_currentSwapchainHeight = 0;
    uint32_t m_previousSwapchainWidth = 0,m_previousSwapchainHeight = 0;

    SDL_GpuBuffer* m_pUberVertexBuffer;
    SDL_GpuBuffer* m_pUberIndexBuffer;

};

#endif //RENDERER_H
