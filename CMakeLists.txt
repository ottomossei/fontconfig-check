cmake_minimum_required(VERSION 3.10)
project(fontconfig-check)

set(CMAKE_CXX_STANDARD 14)

option(WITH_IMAGE_GENERATION "Enable image generation module" OFF)

find_package(Fontconfig REQUIRED)

include_directories(${Fontconfig_INCLUDE_DIRS} ${CMAKE_SOURCE_DIR}/include)

add_library(fontconfig_check src/fontconfig_check.cpp)

if(WITH_IMAGE_GENERATION)
    add_subdirectory(modules/image_generation)
    target_link_libraries(fontconfig_check image_generation_module)
endif()

target_link_libraries(fontconfig_check ${Fontconfig_LIBRARIES})

add_subdirectory(example)
