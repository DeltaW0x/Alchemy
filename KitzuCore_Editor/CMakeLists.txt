cmake_minimum_required(VERSION 3.28)
set(CMAKE_CXX_STANDARD 17)
project(KitzuCore_Editor)


add_executable(${PROJECT_NAME}
        Source/main.cpp
        Source/EditorApp.h
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

add_compile_definitions("DEBUG=$<CONFIG:Debug>")
target_link_libraries(${PROJECT_NAME} PUBLIC KitzuCore_Core)