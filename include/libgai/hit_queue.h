#ifndef __LIBGAI_HIT_QUEUE_H__
#define __LIBGAI_HIT_QUEUE_H__
#include <stddef.h>

#ifdef __cplusplus
extern "C" {
#endif

// Forward declarations
struct gai_hit_queue;
struct gai_hit_queue_operations;
struct gai_hit;



/**
 * Create a new GAI hit queue instance, to free use gai_hit_queue_free()
 *
 * The queue will use the implementation-specific @a operations which make
 * use of the implementtion-specific @a context.
 *
 * The ownership of of @a context is assumed to pass to the queue and the
 * associated data should be freed in the implementation's free operation.
 */
struct gai_hit_queue* gai_hit_queue_new(
    struct gai_hit_queue_operations operations,
    void* context);



/**
 * Frees the GAI hit @a queue instance
 */
void gai_hit_queue_free(struct gai_hit_queue* queue);



/**
 * Retrieves the size of the overhead when transporting hits with the given
 * hit @a queue.
 *
 * Queues which delay the sending of the hits will need to add a queue time
 * property to the hit when it is delivered.
 */
size_t gai_hit_queue_payload_overhead(struct gai_hit_queue* queue);



/**
 * Enqueus the given @a hit to the hit @a queue.
 *
 * The hit may be sent immediately, or (more likely) at a later point depending
 * on the queuing algorithm.
 *
 * @return 0 on success, else an error code
 */
int gai_hit_queue_enqueue(struct gai_hit_queue* queue, struct gai_hit* hit);



/**
 * Retrieve the context for the given GAI hit @a queue
 */
void* gai_hit_queue_get_context(struct gai_hit_queue* queue);



/**
 * The free() operation for the GAI @a queue implementation
 *
 * This should free the contents of the given @a context.
 */
typedef void (*gai_hit_queue_free_op)(void* context);

/**
 * The payload_overhead() operation for the GAI hit @a queue implementation
 */
typedef size_t (*gai_hit_queue_payload_overhead_op)(void* context);

/**
 * The enqueue() operation for the GAI hit @a queue implementation
 */
typedef int (*gai_hit_queue_enqueue_op)(struct gai_hit* hit, void* context);

/**
 * The operations provided by a GAI hit_queue.
 */
struct gai_hit_queue_operations
{
    gai_hit_queue_free_op free;
    gai_hit_queue_payload_overhead_op payload_overhead;
    gai_hit_queue_enqueue_op enqueue;
};

/**
 * Initializes an gai_hit_queue_operations to ensure that all the fields are
 * cleared.
 */
void gai_hit_queue_operations_init(
    struct gai_hit_queue_operations* operations);

#ifdef __cplusplus
}
#endif

#endif // __LIBGAI_HIT_QUEUE_H__
