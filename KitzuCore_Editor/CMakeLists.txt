cmake_minimum_required(VERSION 3.28)
include(FetchContent)
set(CMAKE_CXX_STANDARD 17)
project(KitzuCore_Editor)

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

add_executable(${PROJECT_NAME}
        Source/main.cpp
)
target_link_libraries(${PROJECT_NAME} PUBLIC Alchemy_Core SDL3::SDL3-static flecs::flecs_static Detour)