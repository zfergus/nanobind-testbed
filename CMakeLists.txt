cmake_minimum_required(VERSION 3.18)

project(testbed CXX)

list(APPEND CMAKE_MODULE_PATH "${PROJECT_SOURCE_DIR}/cmake/recipes/")

# Set default minimum C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# Generate position-independent code by default
set(CMAKE_POSITION_INDEPENDENT_CODE ON)

include(nanobind)
nanobind_add_module(testbed bindings.cpp)