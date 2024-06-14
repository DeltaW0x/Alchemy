//
// Created by lucac on 08/06/2024.
//

#ifndef GAME_H
#define GAME_H

#include <flecs.h>
#include <string>
#include "../Renderer/Renderer.h"

struct FrameworkInitInfo {
    SDL_GpuBackend gpuBackend;
    SDL_GpuSwapchainComposition swapchainComposition;
    SDL_GpuPresentMode presentMode;
    SDL_GpuSampleCount msaaSamples;
    std::string windowTitle;
    uint32_t windowWidth,windowHeight,windowFlags;
};



class Application {

public:
    explicit Application(FrameworkInitInfo& initInfo, bool debugMode = false);

    void Run();
    void Quit();

    virtual void Update()  {}
    virtual void Destroy() {}

private:
    void SetupSingletons();
    void SetupSystems();
    void Tick();
    void HandleSDLEvents();

public:
    flecs::world world;

private:
    bool m_bQuit                 = false;
    Renderer* m_pRenderer        = nullptr;
    SDL_GpuDevice *m_pGpuDevice  = NULL;
    SDL_Window    *m_pMainWindow = NULL;
};


#endif //GAME_H
