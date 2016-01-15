project(libgai_curl)
cmake_minimum_required(VERSION 2.8)

include_directories (
  "${PROJECT_SOURCE_DIR}/include"
)

add_subdirectory(src)
add_subdirectory(test)
