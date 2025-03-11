cmake_minimum_required(VERSION 3.31.6)
project(cpp-rlib-tetris VERSION 0.1.0 LANGUAGES C CXX)

#set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

find_package(raylib CONFIG REQUIRED)

include_directories(src)
add_executable(cpp-rlib-tetris 
    src/main.cpp 
    src/grid.cpp
    src/block.cpp
    src/blocks.cpp
    src/position.cpp
    src/colors.cpp
    src/game.cpp
)
target_link_libraries(cpp-rlib-tetris PRIVATE raylib)


