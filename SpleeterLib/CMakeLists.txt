cmake_minimum_required(VERSION 3.14)

project(SpleeterLib)

set(CMAKE_CXX_STANDARD 17)

list(APPEND CMAKE_MODULE_PATH "${PROJECT_SOURCE_DIR}/cmake")

if (WIN32)
  include(runtime)
  set_runtime(DYNAMIC)
  add_definitions(-DNOMINMAX)
endif()

include_directories(src)
add_subdirectory(src)

