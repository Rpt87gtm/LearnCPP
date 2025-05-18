cmake_minimum_required(VERSION 3.23)
project(learnCPP)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# set(CMAKE_CXX_COMPILER clang++)

enable_testing()


add_compile_options(-g -O0 -fprofile-instr-generate -fcoverage-mapping -fno-omit-frame-pointer)

find_package(Catch2 REQUIRED)

include_directories(include)
add_subdirectory(src)
add_subdirectory(test)