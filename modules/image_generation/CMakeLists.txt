if(WITH_IMAGE_GENERATION)
    find_package(Freetype REQUIRED)
    find_package(PkgConfig REQUIRED)
    pkg_check_modules(CAIRO REQUIRED cairo)

    include_directories(${CMAKE_SOURCE_DIR}/modules/image_generation/include)
    include_directories(${FREETYPE_INCLUDE_DIRS})

    add_library(image_generation_module src/image_generation_module.cpp)

    target_link_libraries(image_generation_module ${FREETYPE_LIBRARIES} ${CAIRO_LIBRARIES})
else()
    set(FREETYPE_LIBRARIES "")
    set(CAIRO_LIBRARIES "")
endif()
