cmake_minimum_required(VERSION 3.16)
project(ComputerGraphicsFromScratch CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_subdirectory(vendor/SDL EXCLUDE_FROM_ALL)
# Add sub projects
add_subdirectory(raytracer)
