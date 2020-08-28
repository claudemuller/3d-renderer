cmake_minimum_required(VERSION 3.17)
project(3drenderer C)

set(CMAKE_C_STANDARD 99)

set(SOURCE_FILES src/main.c)
add_executable(3drenderer ${SOURCE_FILES})

find_package(SDL2 REQUIRED)
#find_package(SDL2_image REQUIRED)
#find_package(SDL2_ttf REQUIRED)

include_directories(${PROJECT_SOURCE_DIR}/include)
link_directories(${PROJECT_SOURCE_DIR}/lib)
include_directories(${SDL2_INCLUDE_DIR})
#        ${SDL2_IMAGE_INCLUDE_DIR}
#        ${SDL2_TTF_INCLUDE_DIR})

target_link_libraries(3drenderer ${SDL2_LIBRARY})
#        ${SDL2_IMAGE_LIBRARIES}
#        ${SDL2_TTF_LIBRARIES})