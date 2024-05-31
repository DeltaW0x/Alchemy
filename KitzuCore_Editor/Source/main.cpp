//
// Created by lucac on 28/05/2024.
//

#include <Alchemy.h>

int main() {
    alchemy::Window window("Hello",1280,720);
    alchemy::Renderer renderer(window.GetSdlWindow(), SDL_GPU_BACKEND_VULKAN);
    while(!window.IsQuitting()) {
        window.PollEvent();
        renderer.Draw(SDL_GpuColor{0.11,0.11,0.11,1.0f});

    }
    renderer.Clean();
    window.Clean();
}