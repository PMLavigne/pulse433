include(ExternalProject)

# Config for atmega328
set(MCU_atmega328_H_FUSE 0xd9)
set(MCU_atmega328_L_FUSE 0xc3)
set(MCU_atmega328_SPEED  16000000)

find_program(simulavr
    NAME simulavr
    PATHS "${CMAKE_SOURCE_DIR}/external/avr-tools/toolchain/bin"
    NO_DEFAULT_PATH
    NO_SYSTEM_ENVIRONMENT_PATH
    )

if (NOT simulavr)
    message("-- Could not find simulavr, not building simulator tests!")
else ()
    message("-- Found simulavr: ${simulavr}")

    foreach(mcu IN ITEMS atmega328)

        ExternalProject_Add(cross-avr-${mcu}
            PREFIX "${CMAKE_CURRENT_BINARY_DIR}/avr"
            SOURCE_DIR "${CMAKE_CURRENT_LIST_DIR}/avr"
            BINARY_DIR "${CMAKE_CURRENT_BINARY_DIR}/avr/build/${mcu}"
            STAMP_DIR "${CMAKE_CURRENT_BINARY_DIR}/avr/stamp/${mcu}"
            TMP_DIR "${CMAKE_CURRENT_BINARY_DIR}/avr/tmp/${mcu}"
            BUILD_IN_SOURCE 0
            BUILD_ALWAYS 1
            EXCLUDE_FROM_ALL 0
            CMAKE_ARGS
                "-DCMAKE_TOOLCHAIN_FILE=${CMAKE_CURRENT_LIST_DIR}/avr/cmake/generic-gcc-avr.cmake"
                "-DPROJECT_ROOT=${CMAKE_SOURCE_DIR}"
                "-DAVR_TOOLCHAIN_ROOT=${CMAKE_SOURCE_DIR}/external/avr-tools/toolchain"
                "-DAVR_MCU=${mcu}"
                "-DAVR_H_FUSE=${MCU_${mcu}_H_FUSE}"
                "-DAVR_L_FUSE=${MCU_${mcu}_L_FUSE}"
                "-MCU_SPEED=${MCU_${mcu}_SPEED}"
            INSTALL_COMMAND  ""
            BUILD_BYPRODUCTS "pulse433_TestTransmitter-avr-${mcu}.elf"
            )

        add_custom_command(
            OUTPUT "sim-pulse433_TestTransmitter-avr-${mcu}"
            COMMAND ${simulavr} -v -d ${mcu} -F ${MCU_${mcu}_SPEED} -W 0x20,- -T exit -f "${CMAKE_CURRENT_BINARY_DIR}/avr/build/${mcu}/pulse433_TestTransmitter-avr-${mcu}.elf"
            DEPENDS cross-avr-${mcu}
        )

        message(STATUS "Adding simulation target(s) for MCU: ${mcu}")
        add_custom_target(sim-pulse433_TestTransmitter
            DEPENDS "sim-pulse433_TestTransmitter-avr-${mcu}"
            )

    endforeach()

endif ()
