cmake_minimum_required(VERSION 3.28)
include(FetchContent)
set(CMAKE_CXX_STANDARD 17)
project(KitzuCore_Core_Core)

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

FetchContent_MakeAvailable(SDL flecs recastNavigation)
include_directories(${vectormath_SOURCE_DIR})

add_library(${PROJECT_NAME}
        Source/Alchemy.h
        Source/Window/Window.h
        Source/Window/Window.cpp
        Source/Renderer/Renderer.h
        Source/Renderer/Renderer.cpp
        Source/Miscellaneous/Types.h
        Source/Renderer/backends/imgui_impl_sdlgpu.cpp
        Source/Renderer/backends/imgui_impl_sdlgpu.h
        Source/Renderer/imconfig.h
        Source/Renderer/imgui.cpp
        Source/Renderer/imgui.h
        Source/Renderer/imgui_demo.cpp
        Source/Renderer/imgui_draw.cpp
        Source/Renderer/imgui_internal.h
        Source/Renderer/imgui_tables.cpp
        Source/Renderer/imgui_widgets.cpp
        Source/Renderer/imstb_rectpack.h
        Source/Renderer/imstb_textedit.h
        Source/Renderer/imstb_truetype.h

)
target_include_directories(${PROJECT_NAME} PUBLIC Source)
target_link_libraries(${PROJECT_NAME} PUBLIC SDL3::SDL3-static flecs::flecs_static Detour)