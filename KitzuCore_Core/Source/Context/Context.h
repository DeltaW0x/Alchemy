//
// Created by lucac on 03/06/2024.
//

#ifndef CONTEXT_H
#define CONTEXT_H

#include "imgui/imgui_impl_sdl3.h"
#include "imgui/imgui_impl_sdlgpu.h"
#include "Window/Window.h"
#include "Renderer/Renderer.h"

class Context {
    public:
        Context(bool enableImgui);
        void Run();

private:
    kc::Window* m_pWindow;
    kc::Renderer* m_pRenderer;

    bool m_bImguiEnabled = false;
};



#endif //CONTEXT_H
