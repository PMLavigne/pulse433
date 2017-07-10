
function(add_native_test_build testName)

    set(TEST_TARGET_NAME "${PROJECT_NAME}-test-${testName}")

    add_executable(${TEST_TARGET_NAME}
        ${testName}.cpp
    )

    target_include_directories(${TEST_TARGET_NAME} PUBLIC
        "${CMAKE_SOURCE_DIR}/config"
        )

    target_link_libraries(${TEST_TARGET_NAME} ${PROJECT_NAME} Unity)

    target_compile_features(${TEST_TARGET_NAME} PUBLIC
        cxx_auto_type
        cxx_trailing_return_types
        cxx_return_type_deduction
        cxx_binary_literals
    )

    add_test(${testName} ${TEST_TARGET_NAME})

endfunction()

foreach(testName IN ITEMS ${TEST_LIST})
    add_native_test_build(${testName})
endforeach()
