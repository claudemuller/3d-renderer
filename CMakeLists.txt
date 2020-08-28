cmake_minimum_required(VERSION 3.17)
project(3drenderer C)

set(SOURCE_FILES src/main.c)
set(CMAKE_C_STANDARD 99)

set(SDL2_ROOT    "/usr/local/Cellar/sdl2/2.0.12_1")
set(SDL2_INCLUDE "${SDL2_ROOT}/include")
set(SDL2_LIB     "${SDL2_ROOT}/lib")
set(SDL2_LIBS    "SDL2")

set(PROJECT_INCLUDE "${PROJECT_SOURCE_DIR}/include")
set(PROJECT_LIB     "${PROJECT_SOURCE_DIR}/lib")

# For completion
include_directories(${PROJECT_INCLUDE})
include_directories(${SDL2_INCLUDE})

link_directories(${PROJECT_LIB})
link_directories(${SDL2_LIB})

add_executable(3drenderer ${SOURCE_FILES})

target_link_libraries(3drenderer ${SDL2_LIBS})