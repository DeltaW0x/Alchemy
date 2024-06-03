//
// Created by lucac on 28/05/2024.
//

#include <KitzuCore.h>
#include "imgui/imgui_impl_sdlgpu.h"
#include "imgui/imgui_impl_sdl3.h"

int main() {
    kc::Window window("KitzuCore Editor", 1280, 720,SDL_WINDOW_RESIZABLE);
    kc::Renderer renderer(window.GetSdlWindow(), SDL_GPU_BACKEND_ALL ,SDL_GPU_SWAPCHAINCOMPOSITION_SDR,SDL_GPU_SAMPLECOUNT_1);

    SDL_GpuBuffer* b= SDL_GpuCreateGpuBuffer(SDL_GPU_BUFFERUSAGE_INDIRECT_BIT,100000);
    SDL_GpuDrawPrimitivesIndirect();

    while(!window.IsOpen()) {
        window.PollEvent();
        renderer.BeginDraw();
    }
}
