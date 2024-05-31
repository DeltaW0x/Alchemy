//
// Created by lucac on 27/05/2024.
//

#ifndef WINDOW_H
#define WINDOW_H

#include <SDL3/SDL.h>
#include "../Miscellaneous/Types.h"

namespace kc {
    class Window {
    public:
        Window(){}
        Window(const char *title,u32 with,u32 height,u32 flags = 0);

        void PollEvent();
        void Clean() const;

        bool IsQuitting();

        SDL_Window *GetSdlWindow() const;

    private:
        const char *m_title;
        u32 m_width, m_height;
        bool m_bQuit = false;
        SDL_Window *m_pWindow = nullptr;
    };
} // al

#endif //WINDOW_H
