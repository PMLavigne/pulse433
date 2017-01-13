project("pulse433 Tests" C CXX)
cmake_minimum_required(VERSION 3.2)

add_library(pulse433 INTERFACE)
target_include_directories(pulse433 INTERFACE src)
target_compile_features(pulse433 INTERFACE cxx_strong_enums)

enable_testing()
add_subdirectory(external)
add_subdirectory(test)
