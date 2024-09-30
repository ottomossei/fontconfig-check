cmake_minimum_required(VERSION 3.10)
project(fontconfig-check)

set(CMAKE_CXX_STANDARD 14)

option(WITH_IMAGE_GENERATION "Enable image generation module" OFF)
option(WITH_XTERMINAL_FONT "Enable xterminal font module" OFF)
option(WITH_XTERMINAL_FONT "Enable building example app" ON)

find_package(Fontconfig REQUIRED)

include_directories(${Fontconfig_INCLUDE_DIRS} ${CMAKE_SOURCE_DIR}/include)

add_library(fontconfig_check_static STATIC src/fontconfig_check.cpp)
add_library(fontconfig_check_shared SHARED src/fontconfig_check.cpp)

set_target_properties(fontconfig_check_static PROPERTIES OUTPUT_NAME "fontconfig_check")
set_target_properties(fontconfig_check_shared PROPERTIES OUTPUT_NAME "fontconfig_check")

set_target_properties(fontconfig_check_shared PROPERTIES VERSION 1.0 SOVERSION 1)

target_link_libraries(fontconfig_check_static ${Fontconfig_LIBRARIES})
target_link_libraries(fontconfig_check_shared ${Fontconfig_LIBRARIES})

if(WITH_IMAGE_GENERATION)
    add_subdirectory(modules/image_generation)
    target_link_libraries(fontconfig_check_static image_generation_module)
    target_link_libraries(fontconfig_check_shared image_generation_module)
endif()

if(WITH_XTERMINAL_FONT)
    add_subdirectory(modules/xterminal_font)
    target_link_libraries(fontconfig_check_static xterminal_font_module)
    target_link_libraries(fontconfig_check_shared xterminal_font_module)
endif()

if(WITH_IMAGE_GENERATION)
    add_subdirectory(example)
endif()
