#include "MockHitQueue.h"



const size_t MockHitQueue::PAYLOAD_OVERHEAD_NO_CONTEXT = 123456789;
const int MockHitQueue::ENQUEUE_NO_CONTEXT = -123456789;



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
    return MockHitQueue::PAYLOAD_OVERHEAD_NO_CONTEXT;
}



int NiceMockHitQueue_enqueue_trampoline(struct gai_hit* hit, void* context)
{
    if (context) {
        return static_cast<NiceMockHitQueue*>(context)->enqueue(
            hit, context);
    }
    return MockHitQueue::ENQUEUE_NO_CONTEXT;
}



struct gai_hit_queue* create_nicemocked_gai_hit_queue(
    NiceMockHitQueue* mock)
{
    struct gai_hit_queue_operations operations;
    gai_hit_queue_operations_init(&operations);
    operations.free = NiceMockHitQueue_free_trampoline;
    operations.payload_overhead = NiceMockHitQueue_payload_overhead_trampoline;
    operations.enqueue = NiceMockHitQueue_enqueue_trampoline;
    return gai_hit_queue_new(operations, mock);
}
