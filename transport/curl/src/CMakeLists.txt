include_directories(${CURL_INCLUDE_DIRS})
add_library(gai_curl SHARED
    transport.c
    )
target_link_libraries(gai_curl
    gai
    ${CURL_LIBRARIES})
