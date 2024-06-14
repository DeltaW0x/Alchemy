cmake_minimum_required(VERSION 3.28)
set(CMAKE_CXX_STANDARD 17)
project(KitzuCore_Editor)


add_executable(${PROJECT_NAME}
        Source/main.cpp
        Source/EditorApp.h
)

add_compile_definitions("DEBUG=$<CONFIG:Debug>")
target_link_libraries(${PROJECT_NAME} PUBLIC KitzuCore_Core)