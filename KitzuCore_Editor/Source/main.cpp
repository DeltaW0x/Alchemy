//
// Created by lucac on 28/05/2024.
//

static const bool g_bDebug = true;


#include "EditorApp.h"
int main() {
    FrameworkInitInfo info = {};

    info.gpuBackend = SDL_GPU_BACKEND_ALL;
    info.presentMode = SDL_GPU_PRESENTMODE_VSYNC;
    info.swapchainComposition = SDL_GPU_SWAPCHAINCOMPOSITION_SDR;
    info.windowTitle  = "KitzuCore Editor";
    info.windowWidth = 1280;
    info.windowHeight = 720;
    info.windowFlags = SDL_WINDOW_RESIZABLE;
    info.msaaSamples = SDL_GPU_SAMPLECOUNT_4;
    EditorApp editorApp(info,g_bDebug);
    editorApp.Run();

}

