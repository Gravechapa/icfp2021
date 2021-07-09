cmake_minimum_required(VERSION 3.12)

project(icfpc2021 VERSION 0.1.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

set_property(GLOBAL PROPERTY USE_FOLDERS ON)

message(STATUS "Starting collecting dependencies")

message(STATUS "Collecting project files")

add_subdirectory("${CMAKE_SOURCE_DIR}/thirdparty/cxxopts" "${CMAKE_BINARY_DIR}/cxxopts-bin" EXCLUDE_FROM_ALL)

find_package(OpenSSL 1.1.1 REQUIRED)

add_subdirectory("${CMAKE_SOURCE_DIR}/thirdparty/cpp-httplib" "${CMAKE_BINARY_DIR}/cpp-httplib-bin" EXCLUDE_FROM_ALL)

add_subdirectory("${CMAKE_SOURCE_DIR}/src")