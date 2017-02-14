project(pulse433 C CXX)
cmake_minimum_required(VERSION 3.2)

set(CMAKE_CXX_FLAGS_DEBUG "-O0 -g")
set(CMAKE_C_FLAGS_DEBUG "-O0 -g")
set(CMAKE_CXX_FLAGS_RELEASE "-Os")
set(CMAKE_C_FLAGS_RELEASE "-Os")
set(CMAKE_CXX_FLAGS_RELWITHDEBINFO "-Os -g")
set(CMAKE_C_FLAGS_RELWITHDEBINFO "-Os -g")

set(CMAKE_VERBOSE_MAKEFILE ON)


add_library(pulse433 STATIC src/pulse433.h
                            src/Transmitter.h
                            src/defines.h
                            src/drivers/ArduinoInterruptDriver.h
                            src/drivers/ArduinoInterruptDriver.cpp)
target_include_directories(pulse433 PUBLIC src)
target_compile_features(pulse433 PUBLIC cxx_strong_enums)

enable_testing()
add_subdirectory(external)
add_subdirectory(test)

add_subdirectory(cross)
