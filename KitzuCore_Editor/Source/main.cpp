//
// Created by lucac on 28/05/2024.
//

#include <KitzuCore.h>
#include "EditorRenderer/EditorRenderer.h"

int main() {
    UIStackManager uiManager;

    ASSERT(SDL_Init(SDL_INIT_VIDEO | SDL_INIT_GAMEPAD) == 0, "Failed to init SDL, {0}", SDL_GetError());
    SDL_Window *window = SDL_CreateWindow("KitzuCore Editor", 1280, 720,SDL_WINDOW_RESIZABLE);
    ASSERT(window != nullptr, "Failed to create SDL Window, {0}", SDL_GetError());
    EditorRenderer renderer(window,&uiManager);

    bool running = true;
    while (running) {
        SDL_Event e;
        while (SDL_PollEvent(&e)) {
            ImGui_ImplSDL3_ProcessEvent(&e);
            switch (e.type) {
                case SDL_EVENT_WINDOW_CLOSE_REQUESTED:
                    ImGui_ImplSDLGpu_Shutdown();
                    ImGui_ImplSDL3_Shutdown();
                    renderer.Clean();
                    SDL_DestroyWindow(window);
                    SDL_Quit();
                    return 0;
                break;
            }
        }

        renderer.BeginDraw();
        renderer.EndDraw();
    }
}

