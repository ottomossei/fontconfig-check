cmake_minimum_required(VERSION 3.10)

add_executable(fontconfig_module main.cpp)

if(WITH_IMAGE_GENERATION)
    include_directories(${CMAKE_SOURCE_DIR}/modules/image_generation/include)
    target_link_libraries(fontconfig_module image_generation_module)

    target_compile_definitions(fontconfig_module PRIVATE WITH_IMAGE_GENERATION)
endif()

if(WITH_XTERMINAL_FONT)
    include_directories(${CMAKE_SOURCE_DIR}/modules/xterminal_font/include)
    target_link_libraries(fontconfig_module xterminal_font_module)

    target_compile_definitions(fontconfig_module PRIVATE WITH_XTERMINAL_FONT)
endif()

target_link_libraries(fontconfig_module fontconfig_check_static ${Fontconfig_LIBRARIES})

target_compile_features(fontconfig_familiy PRIVATE cxx_std_14)
