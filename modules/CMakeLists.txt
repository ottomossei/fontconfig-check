cmake_minimum_required(VERSION 3.10)

if(WITH_IMAGE_GENERATION)
    add_subdirectory(image_generation)
endif()
if(WITH_XTERMINAL_FONT)
    add_subdirectory(xterminal_font)
endif()
