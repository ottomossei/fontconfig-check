cmake_minimum_required(VERSION 3.10)

add_executable(fontconfig_attributes main.cpp)

target_link_libraries(fontconfig_attributes fontconfig_check ${Fontconfig_LIBRARIES})

target_compile_features(fontconfig_attributes PRIVATE cxx_std_14)
