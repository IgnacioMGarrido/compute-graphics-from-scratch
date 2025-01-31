cmake_minimum_required(VERSION 3.16)
project(01_Basic_Raytracer CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

file(GLOB_RECURSE SRC_FILES "${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp" "${CMAKE_CURRENT_SOURCE_DIR}/src/*.h" "${CMAKE_CURRENT_SOURCE_DIR}/include/*.h")
add_executable(01_Basic_Raytracer ${SRC_FILES})

target_link_libraries(01_Basic_Raytracer PRIVATE SDL2::SDL2 SDL2::SDL2main)
