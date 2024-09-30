# Define the xterminal_font_module library
add_library(xterminal_font_module STATIC src/xterminal_font_module.cpp)

# Include directories
target_include_directories(xterminal_font_module PUBLIC
    ${CMAKE_SOURCE_DIR}/modules/xterminal_font/include
)


