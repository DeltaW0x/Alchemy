cmake_minimum_required(VERSION 3.28)
set(CMAKE_CXX_STANDARD 17)
project(KitzuCore_Editor)

include(../CommonLibraries.txt)
include(AssimpConfig.txt)

add_executable(${PROJECT_NAME}
        Source/main.cpp
        Source/UIStack/UIStackManager.h
        Source/UIStack/UIElement.h
        Source/EditorRenderer/EditorRenderer.cpp
        Source/EditorRenderer/EditorRenderer.h
        Source/UIStack/Viewport/Viewport.h
)

target_link_libraries(${PROJECT_NAME} PUBLIC
        KitzuCore_Core
        SDL3::SDL3-static
        flecs::flecs_static
        Detour
        assimp::assimp
)