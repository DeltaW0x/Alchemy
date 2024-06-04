cmake_minimum_required(VERSION 3.28)

SET(CMAKE_CXX_STANDARD 17)
project(KitzuCore_Core)

include(../CommonLibraries.txt)

add_library(${PROJECT_NAME}
        Source/KitzuCore.h
        Source/Renderer/Renderer.h
        Source/Renderer/Renderer.cpp
        Source/Miscellaneous/Types.h
        Source/Miscellaneous/Assert.h
        Source/imgui/imconfig.h
        Source/imgui/imgui.cpp
        Source/imgui/imgui.h
        Source/imgui/imgui_demo.cpp
        Source/imgui/imgui_draw.cpp
        Source/imgui/imgui_impl_sdl3.cpp
        Source/imgui/imgui_impl_sdl3.h
        Source/imgui/imgui_impl_sdlgpu.cpp
        Source/imgui/imgui_impl_sdlgpu.h
        Source/imgui/imgui_internal.h
        Source/imgui/imgui_tables.cpp
        Source/imgui/imgui_widgets.cpp
        Source/imgui/imstb_rectpack.h
        Source/imgui/imstb_textedit.h
        Source/imgui/imstb_truetype.h
)

target_include_directories(${PROJECT_NAME} PUBLIC Source)
target_include_directories(${PROJECT_NAME} PUBLIC ${spdlog_SOURCE_DIR}/include)
target_link_libraries(${PROJECT_NAME} PUBLIC SDL3::SDL3-static flecs::flecs_static Detour Jolt spdlog)