add_executable(pulse433_TestTransmitter
    TestTransmitter.cpp
)

target_include_directories(pulse433_TestTransmitter PUBLIC
    "${CMAKE_SOURCE_DIR}/config"
    )

target_link_libraries(pulse433_TestTransmitter pulse433 Unity)
target_compile_features(pulse433_TestTransmitter PUBLIC
    cxx_auto_type
    cxx_trailing_return_types
    cxx_return_type_deduction
    cxx_binary_literals
)

add_test(TestTransmitter pulse433_TestTransmitter)

