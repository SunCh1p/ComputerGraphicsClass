cmake_minimum_required(VERSION 3.16)
project(Assignment1 LANGUAGES CXX)

#set c++ standard
set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

#find opengl
find_package(OpenGL REQUIRED)
find_package(GLU REQUIRED)

#fetch stuff needed to compile the repository
include(FetchContent)
#fetch free glut 3.6.0 from repository
FetchContent_Declare(
    freeglut
    GIT_REPOSITORY https://github.com/FreeGLUTProject/freeglut.git
    GIT_TAG v3.6.0
)
FetchContent_MakeAvailable(freeglut)

#include headers
include_directories(${PROJECT_SOURCE_DIR}/include)

# Main executable
add_executable(Assignment1 src/main.cpp)
target_link_libraries(Assignment1 PRIVATE OpenGL::GL freeglut OpenGL::GLU)