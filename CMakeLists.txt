cmake_minimum_required(VERSION 3.21.7)
project(cpp-rlib-tetris)
set(CMAKE_CXX_STANDARD 17)
if (CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
    set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -static-libgcc -static-libstdc++")
endif()
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

add_custom_command(TARGET cpp-rlib-tetris POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
            "${CMAKE_SOURCE_DIR}/assets"
            "$<TARGET_FILE_DIR:cpp-rlib-tetris>/assets"
    COMMENT "Copying assets folder to output directory")

target_link_libraries(cpp-rlib-tetris PRIVATE raylib)
