set(TEST_EXECUTABLE_NAME graph_test)
set(TEST_NAME GraphTests)

set(TEST_SOURCES
    main.cpp
)

add_executable(${TEST_EXECUTABLE_NAME} ${TEST_SOURCES})

target_link_libraries(${TEST_EXECUTABLE_NAME} PRIVATE Catch2::Catch2WithMain)
target_link_libraries(${TEST_EXECUTABLE_NAME} PRIVATE mgraph)

add_test(
    NAME ${TEST_NAME}
    COMMAND ${TEST_EXECUTABLE_NAME}
    WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}
)

set_property(TEST ${TEST_NAME} PROPERTY ENVIRONMENT 
    "LLVM_PROFILE_FILE=${CMAKE_BINARY_DIR}/coverage/${TEST_EXECUTABLE_NAME}.profraw")
