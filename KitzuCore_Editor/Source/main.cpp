//
// Created by lucac on 28/05/2024.
//

#include <KitzuCore.h>
#include "imgui/imgui_impl_sdlgpu.h"
#include "imgui/imgui_impl_sdl3.h"
int main() {
    kc::Window window("KitzuCore Editor", 1280, 720,SDL_WINDOW_RESIZABLE);
    kc::Renderer renderer(window.GetSdlWindow(), SDL_GPU_BACKEND_ALL,
                                       SDL_GPU_SWAPCHAINCOMPOSITION_SDR,
                                                 SDL_GPU_PRESENTMODE_MAILBOX);
    ImGui_ImplSDLGpu_InitInfo initInfo;
    initInfo.Device               = renderer.GetDevice();
    initInfo.Window               = window.GetSdlWindow();
    initInfo.SwapchainComposition = SDL_GPU_SWAPCHAINCOMPOSITION_SDR;
    initInfo.WindowPresentMode    = SDL_GPU_PRESENTMODE_MAILBOX;
    initInfo.MSAASamples          = SDL_GPU_SAMPLECOUNT_1;

  //  ImGui::CreateContext();
  //  ImGuiIO& io = ImGui::GetIO();
  //  io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;
  //  io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;
  //  io.ConfigFlags |= ImGuiConfigFlags_ViewportsEnable;
  //  ImGui::StyleColorsDark();

 //   ImGui_ImplSDL3_InitForOther(window.GetSdlWindow());
  //  ImGui_ImplSDLGpu_Init(&initInfo);

    bool bQuit = false;
    while (!bQuit) {
        SDL_Event e;
        while (SDL_PollEvent(&e)) {
      //      ImGui_ImplSDL3_ProcessEvent(&e);
            switch (e.type) {
                case SDL_EVENT_WINDOW_CLOSE_REQUESTED:
                    bQuit = true;
                break;
            }
        }
       // ImGui_ImplSDLGpu_NewFrame();
       // ImGui_ImplSDL3_NewFrame();
       // ImGui::NewFrame();
       // ImGui::Begin("Hello Metal!");
       // ImGui::End();
       // ImGui::Render();

        renderer.StartDraw(SDL_GpuColor{0.16f, 0.16f, 0.16f, 1.0f});
       // ImDrawData* draw_data = ImGui::GetDrawData();
       // ImGui_ImplSDLGpu_RenderDrawData(draw_data, renderer.GetMainRenderPass());
        renderer.EndDraw();
      //  if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable)
     //   {
      //      ImGui::UpdatePlatformWindows();
      //      ImGui::RenderPlatformWindowsDefault();
      //  }
    }
    renderer.Clean();
    window.Clean();
}
