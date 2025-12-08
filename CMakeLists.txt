cmake_minimum_required(VERSION 3.26)

project(lib CXX)

include(get_cpm.cmake)

# C++
add_library(example SHARED)
target_include_directories(example PUBLIC lib)
target_sources(
  example
  PRIVATE
    lib/src.cpp
)
target_sources(
  example
  PUBLIC
    FILE_SET HEADERS
      FILES
        lib/src.h
)
install(
  TARGETS
    example
  RUNTIME
    COMPONENT Runtime
  LIBRARY
    COMPONENT Runtime
    NAMELINK_COMPONENT Development
  ARCHIVE
    COMPONENT Development
    DESTINATION lib/static
  FILE_SET HEADERS
    COMPONENT Development
)

# Python
CPMAddPackage(
    NAME pybind11
    GITHUB_REPOSITORY pybind/pybind11
    VERSION 2.13.6
)
find_package(pybind11 REQUIRED)

pybind11_add_module(_example MODULE pylib/bindings.cpp)
target_link_libraries(_example PRIVATE example)
install(
  TARGETS _example
  DESTINATION example
)
install(
  FILES pylib/__init__.py
  DESTINATION example
)
