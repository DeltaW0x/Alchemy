//
// Created by lucac on 08/06/2024.
//

#include "Application.h"
#include "../Logging.h"
#include "ECS/Components/InputComponent.h"
#include "ECS/Systems/InputSystem.h"

static void SDL_LoggerBridge(void *userdata, int category, SDL_LogPriority priority, const char *message) {
    switch(priority) {
        case SDL_LOG_PRIORITY_INFO:
            LOG_INFO(message);
        break;
        case SDL_LOG_PRIORITY_WARN:
            LOG_WARN(message);
        break;
        case SDL_LOG_PRIORITY_ERROR:
            LOG_ERROR(message);
        break;
        case SDL_LOG_PRIORITY_CRITICAL:
            LOG_CRITICAL(message);
        break;
        default:
            break;
    }
}
Application::Application(FrameworkInitInfo &initInfo, bool debugMode) {
    SDL_SetLogOutputFunction(&SDL_LoggerBridge,NULL);
    if (debugMode) {
        initInfo.windowTitle.append(" [DEBUG]");
    }

    LOG_INFO("Initializing SDL");
    ASSERT(SDL_Init(SDL_INIT_VIDEO | SDL_INIT_GAMEPAD) == 0, "Failed to initialize SDL: ", SDL_GetError());

    LOG_INFO("Creating Gpu Device");
    m_pGpuDevice = SDL_GpuCreateDevice(initInfo.gpuBackend, debugMode);
    ASSERT(m_pGpuDevice != NULL, "Failed to create Gpu Device");

    LOG_INFO("Creating main window");
    m_pMainWindow = SDL_CreateWindow(initInfo.windowTitle.c_str(), initInfo.windowWidth, initInfo.windowHeight,
                                  initInfo.windowFlags);
    ASSERT(m_pMainWindow != NULL, "Failed to create main window: ", SDL_GetError());

    LOG_INFO("Claiming main window");
    bool res = SDL_GpuClaimWindow(m_pGpuDevice, m_pMainWindow, initInfo.swapchainComposition, initInfo.presentMode);
    ASSERT(res==SDL_TRUE, "Failed to claim main window");

    m_pRenderer = new Renderer(m_pGpuDevice,m_pMainWindow,initInfo.msaaSamples);

    SetupSingletons();
    SetupSystems();
}

void Application::Run() {
    while (!m_bQuit) {
        Tick();
    }

    LOG_INFO("Shutting down framework");

    LOG_INFO("Shutting down renderer");
    m_pRenderer->Dispose();

    LOG_INFO("Destroying user resources");
    Destroy();

    LOG_INFO("Unclaiming window");
    SDL_GpuUnclaimWindow(m_pGpuDevice, m_pMainWindow);

    LOG_INFO("Destroying window");
    SDL_DestroyWindow(m_pMainWindow);

    LOG_INFO("Destroying Gpu Device");
    SDL_GpuDestroyDevice(m_pGpuDevice);

    LOG_INFO("Quitting SDL");
    SDL_Quit();

    LOG_INFO("See you next time!");
}

void Application::Quit() {
    m_bQuit = true;
}

void Application::SetupSingletons() {
    world.set<InputStateComponent>({});
}

void Application::SetupSystems() {
    flecs::system keyboardInputSystem = world.system<InputStateComponent>()
    .kind(flecs::OnUpdate)
    .term_at(1)
    .singleton()
    .each([](InputStateComponent& inputState) {
        QueryInputState(&inputState);
    });

}

void Application::Tick() {
    HandleSDLEvents();
    if (!m_bQuit) {
        world.progress();
        Update();
        m_pRenderer->StartDraw();
        m_pRenderer->EndDraw();
    }
}

void Application::HandleSDLEvents() {
    SDL_Event e;
    while (SDL_PollEvent(&e)) {
        switch (e.type) {
            case SDL_EVENT_QUIT:
                m_bQuit = true;
            case SDL_EVENT_WINDOW_CLOSE_REQUESTED:
                SDL_Window *window = SDL_GetWindowFromID(e.window.windowID);
                if (window == m_pMainWindow) {
                    m_bQuit = true;
                }
                else {
                    SDL_GpuUnclaimWindow(m_pGpuDevice, window);
                    SDL_DestroyWindow(window);
                }
        }
    }
}
