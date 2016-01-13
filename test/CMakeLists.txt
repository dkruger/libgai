cxx_test(gai_test
    MockTransport.cpp
    assoc_array_test.cpp
    hit_test.cpp
    tracker_test.cpp
    transport_test.cpp
    )
target_link_libraries(gai_test gai)
