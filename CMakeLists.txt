cmake_minimum_required(VERSION 3.21.0)
project(
    MemoryMountain
    VERSION 1.0.0
)
add_executable(${PROJECT_NAME} src/app.c)
target_include_directories(${PROJECT_NAME} PRIVATE include)
