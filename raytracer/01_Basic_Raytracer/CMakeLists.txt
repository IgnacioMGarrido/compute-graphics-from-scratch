cmake_minimum_required(VERSION 3.16)
project(01_Basic_Raytracer CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(01_Basic_Raytracer main.cpp)

# Enlazar GLFW
target_link_libraries(01_Basic_Raytracer PRIVATE glfw)
