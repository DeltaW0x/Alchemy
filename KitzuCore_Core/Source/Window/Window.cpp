//
// Created by lucac on 27/05/2024.
//

#include "Window.h"
#include <Jolt/Jolt.h>
namespace kc {
    Window::Window(const char *title, uint32_t with, uint32_t height,u32 flags) : m_title(title), m_width(with),
                                                                        m_height(height) {
        m_pWindow = SDL_CreateWindow(m_title, m_width, m_height, flags);
        AL_ASSERT(m_pWindow != nullptr, "Failed to create SDL Window: %s", SDL_GetError())
    }

    void Window::PollEvent() {
        SDL_Event e;
        while (SDL_PollEvent(&e)) {
            switch (e.type) {
                case SDL_EVENT_WINDOW_CLOSE_REQUESTED:
                    m_bQuit = true;
                    break;
            }
        }
    }
    bool Window::IsOpen() {
        return m_bQuit;
    }
    void Window::Clean() const {
        SDL_DestroyWindow(m_pWindow);
    }

    SDL_Window *Window::GetSdlWindow() const {
        return m_pWindow;
    }
} // al
