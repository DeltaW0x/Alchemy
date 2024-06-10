cmake_minimum_required(VERSION 3.28)

include(FetchContent)
SET(CMAKE_CXX_STANDARD 17)
project(KitzuCore_Core)

SET(SDL_STATIC ON)

FetchContent_Declare(
        SDL
        GIT_REPOSITORY https://github.com/thatcosmonaut/SDL
        GIT_TAG gpu
)
FetchContent_Declare(
        spdlog
        GIT_REPOSITORY https://github.com/gabime/spdlog.git
        GIT_TAG v1.x
)
FetchContent_Declare(
        flecs
        GIT_REPOSITORY https://github.com/SanderMertens/flecs.git
)

FetchContent_MakeAvailable(SDL spdlog flecs)

add_library(${PROJECT_NAME}
        Source/Application/Application.cpp
        Source/Application/Application.h
        Source/Logging.h
        Source/ECS/Systems/InputSystem.h
        Source/ECS/Components/InputComponent.h
        Source/ECS/Components/MeshComponent.h
        Source/ECS/Components/MaterialComponent.h
        Source/ECS/Components/LightComponent.cpp
        Source/ECS/Components/LightComponent.h
        Source/Renderer/Renderer.cpp
        Source/Renderer/Renderer.h
        Source/ECS/Systems/RenderBatcher.h
)

target_include_directories(${PROJECT_NAME} PUBLIC Source)
target_include_directories(${PROJECT_NAME} PUBLIC ${spdlog_SOURCE_DIR}/include)
target_link_libraries(${PROJECT_NAME} PUBLIC SDL3::SDL3-static flecs_static spdlog)