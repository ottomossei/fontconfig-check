cmake_minimum_required(VERSION 3.10)

add_executable(fontconfig_familiy main.cpp)

target_link_libraries(fontconfig_familiy fontconfig_check_static ${Fontconfig_LIBRARIES})

target_compile_features(fontconfig_familiy PRIVATE cxx_std_14)
