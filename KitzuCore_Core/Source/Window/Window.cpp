//
// Created by lucac on 27/05/2024.
//

#include "Window.h"
#include "Miscellaneous/Assert.h"
#include "imgui/imgui_impl_sdl3.h"
namespace kc {
    Window::Window(const std::string title , uint32_t with, uint32_t height,u32 flags, bool useImgui) : m_title(title),
        m_width(with),
        m_height(height),
        m_bImguiEnabled(useImgui) {
        if(g_bDebug) {
            m_title.append(" [DEBUG]");
        }
        m_pWindow = SDL_CreateWindow(m_title.c_str(), m_width, m_height, flags);
        ASSERT(m_pWindow != nullptr, "Failed to create SDL Window: %s, aborting application", SDL_GetError())
    }

    void Window::PollEvent() {
        SDL_Event e;
        while (SDL_PollEvent(&e)) {
            if(m_bImguiEnabled) {
                ImGui_ImplSDL3_ProcessEvent(&e);
            }
            switch (e.type) {
                case SDL_EVENT_WINDOW_CLOSE_REQUESTED:
                    m_bIsOpen = false;
                    break;
            }
        }
    }

    bool Window::IsOpen() const {
        return m_bIsOpen;
    }

    void Window::Clean() {
        SDL_DestroyWindow(m_pWindow);
    }

    SDL_Window *Window::GetSdlWindow() const {
        return m_pWindow;
    }
} // al
