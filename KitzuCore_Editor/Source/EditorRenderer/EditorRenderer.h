//
// Created by lucac on 04/06/2024.
//

#ifndef EDITORRENDERER_H
#define EDITORRENDERER_H

#include <Renderer/Renderer.h>

class EditorContext;
class EditorRenderer {
public:
    EditorRenderer(EditorContext* context);
    ~EditorRenderer();

    void BeginDraw();
    void DrawUI();
    void EndDraw();

    Renderer* GetLowLevelRenderer();

private:
    SDL_GpuTexture *m_pHdrRenderTarget;
    SDL_GpuTexture *m_pSdrRenderTarget;

    SDL_GpuCommandBuffer *m_pMainCmdBuffer;

    SDL_GpuTextureCreateInfo m_pHdrRenderTargetInfo = {};
    SDL_GpuTextureCreateInfo m_pSdrRenderTargetInfo = {};

    SDL_GpuSampler *m_pViewportTextureSampler;
    SDL_GpuTextureSamplerBinding m_viewportTextureSamplerBinding = {};

    SDL_GpuTextureSamplerBinding m_binding;

private:
    ImVec2 m_currentViewportSize;
    ImVec2 m_previousVieportSize;
    EditorContext* m_pCtx;
    Renderer *m_pLowLevelRenderer;
};


#endif //EDITORRENDERER_H
