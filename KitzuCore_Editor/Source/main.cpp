//
// Created by lucac on 28/05/2024.
//

#ifdef _DEBUG
static const bool g_bDebug = true;
#else
static const bool g_bDebug = false;
#endif

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

    EditorApp editorApp(info,g_bDebug);
    editorApp.Run();

}

