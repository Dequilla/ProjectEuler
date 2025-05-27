cmake_minimum_required(VERSION 3.28)

set(PROJECT_NAME euler)

project(
    ${PROJECT_NAME}_proj
    VERSION 0.1
    DESCRIPTION "Programming and maths practice."
    LANGUAGES C CXX
)

set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 26)

if(UNIX)
    # Primarily for ubuntu who ships old shit
    set(CMAKE_C_COMPILER gcc-13)
    set(CMAKE_CXX_COMPILER g++-13)
endif()

add_executable(${PROJECT_NAME})
target_sources(${PROJECT_NAME} PRIVATE main.cpp)

