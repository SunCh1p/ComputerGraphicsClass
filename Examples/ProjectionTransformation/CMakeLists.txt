cmake_minimum_required(VERSION 3.16)
project(ProjectionTransformation LANGUAGES CXX)

# Set C++ standard
set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# Find OpenGL glut
find_package(OpenGL REQUIRED)
find_package(GLUT REQUIRED)

# Main executable
add_executable(ProjectionTransformation main.cpp)
target_link_libraries(ProjectionTransformation PRIVATE OpenGL::GL GLUT::GLUT OpenGL::GLU)