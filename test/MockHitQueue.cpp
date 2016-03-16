#include "MockHitQueue.h"



const size_t MockHitQueue::INVALID_PAYLOAD_OVERHEAD = 123456789;



void NiceMockHitQueue_free_trampoline(void* context)
{
    if (context) {
        static_cast<NiceMockHitQueue*>(context)->free(context);
    }
}



size_t NiceMockHitQueue_payload_overhead_trampoline(void* context)
{
    if (context) {
        return static_cast<NiceMockHitQueue*>(context)->payload_overhead(
            context);
    }
    return MockHitQueue::INVALID_PAYLOAD_OVERHEAD;
}



struct gai_hit_queue* create_nicemocked_gai_hit_queue(
    NiceMockHitQueue* mock)
{
    struct gai_hit_queue_operations operations;
    gai_hit_queue_operations_init(&operations);
    operations.free = NiceMockHitQueue_free_trampoline;
    operations.payload_overhead = NiceMockHitQueue_payload_overhead_trampoline;
    return gai_hit_queue_new(operations, mock);
}
