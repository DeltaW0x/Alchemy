//
// Created by lucac on 28/05/2024.
//

#include <KitzuCore.h>
#include <ctime>
#include <ratio>
#include <chrono>
#include <iostream>
#include "imgui/imgui_impl_sdlgpu.h"
#include "imgui/imgui_impl_sdl3.h"

using  namespace std::chrono;
int main() {
    kc::Window window("KitzuCore Editor", 1280, 720,SDL_WINDOW_RESIZABLE);
    kc::Renderer renderer(window.GetSdlWindow(), SDL_GPU_BACKEND_VULKAN ,SDL_GPU_SWAPCHAINCOMPOSITION_SDR,SDL_GPU_SAMPLECOUNT_1);

    /*
    ImGui_ImplSDLGpu_InitInfo initInfo;
    initInfo.Device = renderer.GetDevice();
    initInfo.Window = window.GetSdlWindow();
    initInfo.SwapchainComposition = renderer.GetSwapchainComposition();
    initInfo.WindowPresentMode = renderer.GetPresentMode();
    initInfo.MSAASamples = SDL_GPU_SAMPLECOUNT_2;

    ImGui::CreateContext();
    ImGuiIO &io = ImGui::GetIO();
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;
    io.ConfigFlags |= ImGuiConfigFlags_ViewportsEnable;
    ImGui::StyleColorsDark();

    ImGui_ImplSDL3_InitForOther(window.GetSdlWindow());
    ImGui_ImplSDLGpu_Init(&initInfo);
*/
    int sum = 0;

    high_resolution_clock::time_point t1 = high_resolution_clock::now();
    int i = 0;
    bool bQuit = false;
    while (!bQuit) {
        SDL_Event e;
        while (SDL_PollEvent(&e)) {
           // ImGui_ImplSDL3_ProcessEvent(&e);
            switch (e.type) {
                case SDL_EVENT_WINDOW_CLOSE_REQUESTED:
                    bQuit = true;
                    break;
            }
        }

        renderer.BeginDraw();
        renderer.EndDraw();
       
       
       
       
        high_resolution_clock::time_point t2 = high_resolution_clock::now();
        std::chrono::milliseconds time_span = duration_cast<std::chrono::milliseconds>(t2-t1);
        std::cout << time_span.count() << std::endl;
        t1 = t2;
       
/*
        if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable) {
            ImGui::UpdatePlatformWindows();
            ImGui::RenderPlatformWindowsDefault();
        }
        */
    }
   // renderer.Clean();
   // window.Clean();
}
