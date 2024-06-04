//
// Created by lucac on 04/06/2024.
//

#ifndef EDITORRENDERER_H
#define EDITORRENDERER_H
#include "../UIStack/UIStackManager.h"
#include "../UIStack/Viewport/Viewport.h"
#include <Renderer/Renderer.h>
#include <imgui/imgui_impl_sdl3.h>
#include <imgui/imgui_impl_sdlgpu.h>

class EditorRenderer {

public:
    EditorRenderer(SDL_Window* window,UIStackManager* uiManager);

    void BeginDraw();
    void DrawUI();
    void EndDraw();
    void Clean();
    void SetupImGuiStyle();

private:
    SDL_GpuTexture* m_pHdrRenderTarget;
    SDL_GpuTexture* m_pSdrRenderTarget;

    SDL_GpuCommandBuffer* m_pMainCmdBuffer;

    SDL_GpuTextureCreateInfo m_pHdrRenderTargetInfo = {};
    SDL_GpuTextureCreateInfo m_pSdrRenderTargetInfo = {};

    SDL_GpuSampler* m_pViewportTextureSampler;
    SDL_GpuTextureSamplerBinding m_viewportTextureSamplerBinding = {};

    SDL_GpuTextureSamplerBinding m_binding;

private:
    Renderer* m_pLowLevelRenderer;
    UIStackManager* m_pUiStackManager;
    Viewport m_Viewport;
    ImVec2 m_currentViewportSize;
    ImVec2 m_previousVieportSize;
};



#endif //EDITORRENDERER_H
