cmake_minimum_required(VERSION 3.10)

project(MiniCLIParser)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)


# Library

add_library(mini_cli INTERFACE)

target_include_directories(mini_cli INTERFACE include)


# Example executable

add_executable(example_app examples/main.cpp)

target_link_libraries(example_app PRIVATE mini_cli)