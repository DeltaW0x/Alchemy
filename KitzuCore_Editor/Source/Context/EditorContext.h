//
// Created by lucac on 04/06/2024.
//

#ifndef EDITORCONTEXT_H
#define EDITORCONTEXT_H

#include <KitzuCore.h>
#include "../EditorRenderer/EditorRenderer.h"
#include "../UIStack/UILayer.h"
#include <imgui/imgui_impl_sdl3.h>
#include <imgui/imgui_impl_sdlgpu.h>

class EditorContext {
public:
    EditorContext();

    int Run();

    EditorRenderer* GetEditorRender();
    SDL_Window* GetWindow();
    UILayer* GetUILayer();

private:
    void Quit();
    void CustomImGuiTheme();
private:
    EditorRenderer* m_pEditorRenderer;
    SDL_Window* m_pWindow;
    UILayer* m_pUILayer;
};


#endif //EDITORCONTEXT_H
