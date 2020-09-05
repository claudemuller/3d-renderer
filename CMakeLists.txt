cmake_minimum_required(VERSION 3.17)
project(3drenderer C)

set(SOURCE_FILES src/main.c
        src/display.c src/display.h
        src/colours.h src/colours.c
        src/benchmark.h src/benchmark.c
        src/vector.c src/vector.h src/constants.h src/mesh.h src/mesh.c src/triangle.h src/triangle.c)
set(CMAKE_C_STANDARD 99)

set(SDL2_ROOT    "D:/libs/sdl2")
if(${CMAKE_SYSTEM_NAME} MATCHES "Darwin")
    set(SDL2_ROOT    "/usr/local/Cellar/sdl2/2.0.12_1")
endif(${CMAKE_SYSTEM_NAME} MATCHES "Darwin")
if(${CMAKE_SYSTEM_NAME} MATCHES "Linux")
    set(SDL2_ROOT    "/usr/local/sdl2")
endif(${CMAKE_SYSTEM_NAME} MATCHES "Linux")

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