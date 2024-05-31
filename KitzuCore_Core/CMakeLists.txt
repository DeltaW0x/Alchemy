cmake_minimum_required(VERSION 3.28)

SET(CMAKE_CXX_STANDARD 17)
project(KitzuCore_Core)

include(../Common_Cmake.txt)

add_library(${PROJECT_NAME}
        Source/KitzuCore.h
        Source/Window/Window.h
        Source/Window/Window.cpp
        Source/Renderer/Renderer.h
        Source/Renderer/Renderer.cpp
        Source/Miscellaneous/Types.h
)

SET_INTERPROCEDURAL_OPTIMIZATION()

target_include_directories(${PROJECT_NAME} PUBLIC Source)
target_link_libraries(${PROJECT_NAME} PUBLIC SDL3::SDL3-static flecs::flecs_static Detour Jolt)