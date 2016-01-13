project(libgai)
cmake_minimum_required(VERSION 2.8)

find_package(Threads)
include("cmake/GMock.cmake")

set(CMAKE_C_FLAGS "-Wall -Wextra -Wno-typedef-redefinition")
set(CMAKE_C_FLAGS_DEBUG "-g -O0")

include_directories (
  "${PROJECT_SOURCE_DIR}"
  "${PROJECT_SOURCE_DIR}/src"
  "${PROJECT_SOURCE_DIR}/include"
)

add_subdirectory(src)
add_subdirectory(test)
add_subdirectory(transport)
