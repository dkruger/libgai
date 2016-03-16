#include "libgai/hit_queue.h"
#include <stdlib.h>



// Define the gai_hit_queue struct, its contents are private
struct gai_hit_queue {
    struct gai_hit_queue_operations operations;
    void* context;
};



struct gai_hit_queue* gai_hit_queue_new(
    struct gai_hit_queue_operations operations,
    void* context)
{
    struct gai_hit_queue* queue = malloc(sizeof(struct gai_hit_queue));
    queue->operations = operations;
    queue->context = context;
    return queue;
}



void gai_hit_queue_free(struct gai_hit_queue* queue)
{
    if (queue && queue->operations.free) {
        // Run the implementation free which should free the context
        queue->operations.free(queue->context);
        queue->context = NULL;
    }
    free(queue);
}



size_t gai_hit_queue_payload_overhead(struct gai_hit_queue* queue)
{
    if (queue && queue->operations.payload_overhead) {
        // Run the implementation serialiation
        return queue->operations.payload_overhead(queue->context);
    }
    return 0;
}



int gai_hit_queue_enqueue(struct gai_hit_queue* queue, struct gai_hit* hit)
{
    if (queue && queue->operations.enqueue) {
        // Run the implementation serialiation
        return queue->operations.enqueue(hit, queue->context);
    }
    return -1;
}



void* gai_hit_queue_get_context(struct gai_hit_queue* queue)
{
    return queue->context;
}



void gai_hit_queue_operations_init(struct gai_hit_queue_operations* operations)
{
    operations->free = NULL;
    operations->payload_overhead = NULL;
    operations->enqueue = NULL;
}
