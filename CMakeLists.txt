cmake_minimum_required(VERSION 3.30)
project(glfw_demo)

set(CMAKE_CXX_STANDARD 20)

find_package(glfw3 3.4 REQUIRED)

find_package(OpenGL REQUIRED)

add_executable(glfw_demo main.cpp)

target_link_libraries(glfw_demo glfw OpenGL::GL)
