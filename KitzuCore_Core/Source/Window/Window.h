//
// Created by lucac on 27/05/2024.
//

#ifndef WINDOW_H
#define WINDOW_H

#include <SDL3/SDL.h>
#include <string>
#include "Miscellaneous/Types.h"


namespace kc {
    class Window {
    public:
        Window(){}
        Window(const std::string title,u32 with,u32 height,u32 flags = 0,bool useImgui = false);

        void PollEvent();
        void Clean();

        [[nodiscard]] bool IsOpen() const;

        [[nodiscard]] SDL_Window *GetSdlWindow() const;

    private:
        std::string m_title;
        u32 m_width, m_height;

        bool m_bIsOpen = true;
        bool m_bImguiEnabled = false;

        SDL_Window *m_pWindow = nullptr;
    };
} // al

#endif //WINDOW_H
