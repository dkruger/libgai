cxx_test(gai_test
    MockHitQueue.cpp
    MockTransport.cpp
    assoc_array_test.cpp
    hit_test.cpp
    hit_event_test.cpp
    hit_queue_test.cpp
    tracker_test.cpp
    transport_test.cpp
    )
target_link_libraries(gai_test gai)
