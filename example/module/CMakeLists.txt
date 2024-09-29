cmake_minimum_required(VERSION 3.10)

add_executable(fontconfig_module main.cpp)

if(WITH_IMAGE_GENERATION)
    include_directories(${CMAKE_SOURCE_DIR}/modules/image_generation/include)
    target_link_libraries(fontconfig_module image_generation_module)

    target_compile_definitions(fontconfig_module PRIVATE WITH_IMAGE_GENERATION)
endif()

target_link_libraries(fontconfig_module fontconfig_check ${Fontconfig_LIBRARIES})
