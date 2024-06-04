//
// Created by lucac on 03/06/2024.
//

#include "Context.h"
#include "imgui/imgui_impl_sdl3.h"
#include "imgui/imgui_impl_sdlgpu.h"
#include "Miscellaneous/Assert.h"
#include <SDL3/SDL.h>

#include "Renderer/Renderer.h"

Context::Context(bool enableImgui)  : m_bImguiEnabled(enableImgui)
{
    ASSERT(SDL_Init(SDL_INIT_VIDEO) == 0, "Failed to init SDL, aborting application", SDL_GetError())

    m_pWindow  = new kc::Window("KitzuCore Editor", 1280, 720,SDL_WINDOW_RESIZABLE,m_bImguiEnabled);
    m_pRenderer = new kc::Renderer(m_pWindow->GetSdlWindow(), SDL_GPU_BACKEND_ALL, SDL_GPU_SWAPCHAINCOMPOSITION_SDR,SDL_GPU_SAMPLECOUNT_1, SDL_GPU_PRESENTMODE_VSYNC,m_bImguiEnabled);

    if(m_bImguiEnabled) {
        ImGui::CreateContext();
        ImGuiIO& io = ImGui::GetIO(); (void)io;
        io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;
        io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;
        io.ConfigFlags |= ImGuiConfigFlags_ViewportsEnable;
        ImGui::StyleColorsDark();

        ImGui_ImplSDLGpu_InitInfo initInfo = {};
        initInfo.Device = m_pRenderer->GetDevice();
        initInfo.Window = m_pWindow->GetSdlWindow();
        initInfo.MSAASamples = SDL_GPU_SAMPLECOUNT_1;
        initInfo.WindowPresentMode = SDL_GPU_PRESENTMODE_VSYNC;
        initInfo.SwapchainComposition = SDL_GPU_SWAPCHAINCOMPOSITION_SDR;

        ImGui_ImplSDL3_InitForOther(m_pWindow->GetSdlWindow());
        ImGui_ImplSDLGpu_Init(&initInfo);
    }
}

void Context::Run() {
    while(m_pWindow->IsOpen()) {
        m_pWindow->PollEvent();
        if(m_bImguiEnabled) {
            ImGui_ImplSDL3_NewFrame();
            ImGui_ImplSDLGpu_NewFrame();
            ImGui::NewFrame();
            ImGui::Begin("Hello!");
            ImGui::End();
            ImGui::Render();
        }
        m_pRenderer->BeginDraw();
        m_pRenderer->EndDraw();

        if(m_bImguiEnabled) {
            ImGuiIO& io = ImGui::GetIO(); (void)io;
            if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable)
            {
                ImGui::UpdatePlatformWindows();
                ImGui::RenderPlatformWindowsDefault();
            }
        }
    }
}
