cmake_minimum_required(VERSION 3.28)
project(Alchemy)
include(FetchContent)

set(CMAKE_CXX_STANDARD 17)
set(SDL_STATIC ON)
set(CMAKE_POLICY_DEFAULT_CMP0077 NEW)
SET(RECASTNAVIGATION_DEMO OFF)
SET(RECASTNAVIGATION_TESTS OFF)
SET(RECASTNAVIGATION_EXAMPLES OFF)
SET(RECASTNAVIGATION_DT_POLYREF64 OFF)
SET(RECASTNAVIGATION_DT_VIRTUAL_QUERYFILTER OFF)

FetchContent_Declare(
        SDL
        GIT_REPOSITORY https://github.com/thatcosmonaut/SDL
        GIT_TAG gpu
)

FetchContent_Declare(
        flecs
        GIT_REPOSITORY https://github.com/SanderMertens/flecs.git
)

FetchContent_Declare(
        recastNavigation
        GIT_REPOSITORY https://github.com/recastnavigation/recastnavigation.git
        GIT_TAG main
)
FetchContent_Declare(
        DirectXMath
        GIT_REPOSITORY https://github.com/microsoft/DirectXMath.git
        GIT_TAG main
)
FetchContent_MakeAvailable(SDL flecs recastNavigation DirectXMath)

IF (NOT WIN32)
    include_directories(Source/Platform/sal/)
ENDIF()

add_executable(${PROJECT_NAME} Source/main.cpp
        Source/Math/Float2.h
        Source/Math/Float3.h
        Source/Precompiled/stdafx.h
        Source/Math/Float4.h
        Source/Math/MatrixMath.h
        Source/Window/Window.cpp
        Source/Window/Window.h
        Source/Miscellaneous/Types.h
        Source/Renderer/Renderer.cpp
        Source/Renderer/Renderer.h
        Source/ECS/Transform.h
        Source/ECS/Rendering/StaticMesh.h
        Source/Platform/sal/sal.h
)

include_directories(Source/Precompiled)
target_link_libraries(${PROJECT_NAME} PRIVATE SDL3::SDL3-static flecs::flecs_static Detour DirectXMath)


