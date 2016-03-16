#ifndef __LIBGAI_TEST_MOCKHITQUEUE_H__
#define __LIBGAI_TEST_MOCKHITQUEUE_H__
#include <gmock/gmock.h>
#include "libgai/hit_queue.h"



/**
 * A simple hit queue object which can be mocked to make testing easier
 */
class MockHitQueue
{
public:
    static const size_t INVALID_PAYLOAD_OVERHEAD;
    MOCK_METHOD1(free, void(void* context));
    MOCK_METHOD1(payload_overhead, size_t(void* context));
};

/**
 * A typedef for making a NiceMock of the mock hit queue
 */
typedef ::testing::NiceMock<MockHitQueue> NiceMockHitQueue;

/**
 * Trampoline function for NiceMockHitQueue::free()
 */
void NiceMockHitQueue_free_trampoline(void* context);

/**
 * Trampoline function for NiceMockHitQueue::payload_overhead()
 */
size_t NiceMockHitQueue_payload_overhead_trampoline(void* context);

/**
 * Creates a GAI hit queue instance using gai_hit_queue_new(), providing the
 * mock @a queue as the implementation
 */
struct gai_hit_queue* create_nicemocked_gai_hit_queue(
    NiceMockHitQueue* queue);

#endif // __LIBGAI_TEST_MOCKHITQUEUE_H__
