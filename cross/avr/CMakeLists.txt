cmake_minimum_required(VERSION 3.2)

include(cmake/generic-gcc-avr.cmake)

project(pulse433 C CXX)

message(STATUS "Generating ${AVR_MCU} build configurations for tests: ${TEST_LIST}")

set(CMAKE_CXX_FLAGS_DEBUG "-O0 -g")
set(CMAKE_C_FLAGS_DEBUG "-O0 -g")
set(CMAKE_CXX_FLAGS_RELEASE "-Os")
set(CMAKE_C_FLAGS_RELEASE "-Os")
set(CMAKE_CXX_FLAGS_RELWITHDEBINFO "-Os -g")
set(CMAKE_C_FLAGS_RELWITHDEBINFO "-Os -g")

add_avr_library(pulse433-avr STATIC
    "${CMAKE_SOURCE_DIR}/src/pulse433.h"
    "${CMAKE_SOURCE_DIR}/src/defines.h"
    "${CMAKE_SOURCE_DIR}/src/drivers/Driver.h"
    "${CMAKE_SOURCE_DIR}/src/Transmitter.h"
    "${CMAKE_SOURCE_DIR}/src/Transmitter.cpp"
    "${CMAKE_CURRENT_LIST_DIR}/src/drivers/AbstractAVRDriver.h"
    "${CMAKE_CURRENT_LIST_DIR}/src/drivers/AbstractAVRDriver.cpp"
    "${CMAKE_CURRENT_LIST_DIR}/src/drivers/AVRLoopDriver.h"
    "${CMAKE_CURRENT_LIST_DIR}/src/drivers/AVRLoopDriver.cpp"
    "${CMAKE_CURRENT_LIST_DIR}/src/drivers/AVRInterruptDriver.h"
    "${CMAKE_CURRENT_LIST_DIR}/src/drivers/AVRInterruptDriver.cpp"
    )

avr_target_compile_options(pulse433-avr PUBLIC
    "-DF_CPU=${MCU_SPEED}UL"
    "-fpack-struct"
    "-fshort-enums"
    "-funsigned-char"
    "-funsigned-bitfields"
    "-ffunction-sections"
    "-Wall"
    "-Wextra"
    "-c"
    )

avr_target_compile_features(pulse433-avr PUBLIC cxx_strong_enums)

avr_target_include_directories(pulse433-avr PUBLIC "${CMAKE_SOURCE_DIR}/src")

add_avr_library(unity-avr "${CMAKE_SOURCE_DIR}/external/Unity/src/unity.c")

avr_target_include_directories(unity-avr PUBLIC
    "${CMAKE_SOURCE_DIR}/external/Unity/src"
    "${CMAKE_SOURCE_DIR}/config/"
    )

avr_target_compile_options(unity-avr PRIVATE
    "-DUNITY_INCLUDE_CONFIG_H"
    )

avr_target_compile_options(unity-avr PUBLIC
    "-DF_CPU=${MCU_SPEED}UL"
    "-DUNITY_EXCLUDE_STDINT_H"
    "-DUNITY_EXCLUDE_LIMITS_H"
    "-DUNITY_EXCLUDE_SIZEOF"
    "-DUNITY_EXCLUDE_DOUBLE"
    "-DUNITY_SUPPORT_TEST_CASES"
    "-DUNITY_INT_WIDTH=16"
    "-DUNITY_LONG_WIDTH=32"
    "-DUSE_SIMULAVR"
    "-fpack-struct"
    "-fshort-enums"
    "-funsigned-char"
    "-funsigned-bitfields"
    "-ffunction-sections"
    "-Wall"
    "-Wextra"
    "-c"
    )

function(add_avr_test_build testName)
    set(TEST_TARGET "${CMAKE_PROJECT_NAME}-test-${testName}-avr")

    add_avr_executable(${TEST_TARGET}
        ${CMAKE_SOURCE_DIR}/test/${testName}.cpp
        )

    avr_target_link_libraries(${TEST_TARGET}
        pulse433-avr
        unity-avr
        )


    avr_target_compile_options(${TEST_TARGET} PUBLIC
        "-DF_CPU=${MCU_SPEED}UL"
        "-fpack-struct"
        "-fshort-enums"
        "-funsigned-char"
        "-funsigned-bitfields"
        "-ffunction-sections"
        "-Wall"
        "-Wextra"
        "-c"
        )

    avr_target_compile_features(${TEST_TARGET} PUBLIC
        cxx_auto_type
        cxx_trailing_return_types
        cxx_return_type_deduction
        cxx_binary_literals
        )
endfunction()

foreach(testName IN ITEMS ${TEST_LIST})
    message(STATUS "Adding test executable build for ${AVR_MCU}: ${testName}")
    add_avr_test_build(${testName})
endforeach()
