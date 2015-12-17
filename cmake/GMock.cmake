
# gmock.

include(ExternalProject)

ExternalProject_Add(gmock_ext
        SVN_REPOSITORY "http://googlemock.googlecode.com/svn/tags/release-1.7.0"
        BINARY_DIR "${CMAKE_BINARY_DIR}/third-party/gmock-build"
        SOURCE_DIR "${CMAKE_BINARY_DIR}/third-party/gmock-src"
        CMAKE_ARGS "${gmock_cmake_args}"
        UPDATE_COMMAND ""
        INSTALL_COMMAND ""
        )

enable_testing()
link_directories("${CMAKE_BINARY_DIR}/third-party/gmock-build")
include_directories(
    "${CMAKE_BINARY_DIR}/third-party/gmock-src/include"
    "${CMAKE_BINARY_DIR}/third-party/gmock-src/gtest/include"
    )

find_package(Threads)

function(cxx_test name)
    add_executable(${name} ${ARGN})
    target_link_libraries(${name} gmock_main gmock ${CMAKE_THREAD_LIBS_INIT})
    add_dependencies(${name} gmock_ext)
    # Working directory: where the dlls are installed.
    add_test(NAME ${name} COMMAND ${name})
endfunction()
