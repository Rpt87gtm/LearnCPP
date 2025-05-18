set(TEST_EXECUTABLE_NAME agent_tests)

set(TEST_SOURCES
    main.cpp
)

add_executable(${TEST_EXECUTABLE_NAME} ${TEST_SOURCES})

target_link_libraries(${TEST_EXECUTABLE_NAME} PRIVATE Catch2::Catch2WithMain)

add_test(
    NAME VectorTest
    COMMAND ${TEST_EXECUTABLE_NAME}
    WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}
)

set_property(TEST VectorTest PROPERTY ENVIRONMENT 
    "LLVM_PROFILE_FILE=${CMAKE_BINARY_DIR}/coverage/${TEST_EXECUTABLE_NAME}.profraw")
