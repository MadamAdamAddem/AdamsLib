cmake_minimum_required(VERSION 3.10.0)
project(test VERSION 0.1.0 LANGUAGES C CXX)


file(GLOB_RECURSE SOURCES CONFIGURE_DEPENDS src/*.cpp src/headers/*.hpp)

add_executable(adamLib ${SOURCES})

find_library(SDL2_LIB SDL2)
find_library(SDL2_LIB_IMG SDL2_image)
find_library(SDL2_LIB_TTF SDL2_ttf)
find_library(TMX tmxlite)

target_link_libraries(adamLib PRIVATE ${SDL2_LIB} ${SDL2_LIB_IMG} ${SDL2_LIB_TTF} ${TMX})