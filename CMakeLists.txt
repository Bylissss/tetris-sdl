cmake_minimum_required(VERSION 3.16)
project(tetris-sdl)

set(SDL_TEST OFF CACHE BOOL "" FORCE)
set(SDL_SHARED ON CACHE BOOL "" FORCE)

add_subdirectory(SDL)

add_executable(${PROJECT_NAME} tetris.c)

target_link_libraries(${PROJECT_NAME} PRIVATE SDL3::SDL3)