cmake_minimum_required(VERSION 3.26)

project(lib CXX)

include(get_cpm.cmake)

option(BUILD_PYTHON_PACKAGE OFF)
if (BUILD_PYTHON_PACKAGE)
  set(LIBRARY_INSTALL_DESTINATION example)
else()
  set(LIBRARY_INSTALL_DESTINATION lib)
endif()
set(origin_token "$ORIGIN")
# C++
add_library(example SHARED)
target_include_directories(
  example
  PUBLIC lib
)
target_sources(
  example
  PUBLIC
    FILE_SET HEADERS
      FILES
        lib/src.h
  PRIVATE
    lib/src.cpp
)
install(
  TARGETS
    example
  LIBRARY
    COMPONENT Runtime
    DESTINATION ${LIBRARY_INSTALL_DESTINATION}
    NAMELINK_COMPONENT Development
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
  TARGETS
    _example
  LIBRARY
    COMPONENT PythonPackage
    DESTINATION ${LIBRARY_INSTALL_DESTINATION}
)
install(
  FILES pylib/__init__.py
  DESTINATION ${LIBRARY_INSTALL_DESTINATION}
  COMPONENT PythonPackage
)
