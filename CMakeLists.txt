cmake_minimum_required(VERSION 3.10)
project(big_integer)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O3 -pthread -Wall")
set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -fsanitize=address,undefined -D_GLIBCXX_DEBUG")
enable_language(ASM_NASM)

include_directories(${PROJECT_SOURCE_DIR}/)

add_executable(big_integer
                big_integer_testing.cpp
                big_integer.cpp
                gtest/gtest-all.cc
                gtest/gtest_main.cc
                engine/_asm_vector.asm
                _core_arithmetics.cpp
                vector.hpp shared_ptr.hpp)
