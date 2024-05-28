#include "Precompiled/stdafx.h"
#include "Renderer/Renderer.h"
#include "Window/Window.h"

int main() {
    SDL_Init(SDL_INIT_VIDEO | SDL_INIT_GAMEPAD);
    alchemy::Window window("Alchemy",1280,720,SDL_WINDOW_RESIZABLE);
    alchemy::Renderer renderer(window.GetSdlWindow(),SDL_GPU_BACKEND_ALL);

    flecs::world w;
    /*
    while(!window.IsQuitting()) {
        window.PollEvent();
        renderer.Draw(SDL_GpuColor{0.16f,0.16f,0.16f,1.0});
    }
*/
    renderer.Clean();
    window.Clean();
    return 0;
}
