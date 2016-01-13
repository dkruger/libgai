#ifndef __LIBGAI_TRANSPORT_H__
#define __LIBGAI_TRANSPORT_H__

#ifdef __cplusplus
extern "C" {
#endif

// Forward declarations
struct gai_transport;
struct gai_transport_operations;



/**
 * Create a new GAI transport instance, to free use gai_transport_free()
 *
 * The transport will use the implementation-specific @a operations which make
 * use of the implementtion-specific @a context
 *
 * The ownership of of @a context is assumed to pass to the transport and the
 * associated data should be freed in the implementation's free operation.
 */
struct gai_transport* gai_transport_new(
    struct gai_transport_operations operations,
    void* context);



/**
 * Frees the @a transport instance
 */
void gai_transport_free(struct gai_transport* transport);



/**
 * Retrieve the context for the given GAI @a transport.
 */
void* gai_transport_get_context(struct gai_transport* transport);



/**
 * The free() operation for the GAI transport implementation
 *
 * This should free the contents of the given @a context.
 */
typedef void (*gai_transport_free_op)(
    void* context);

/**
 * The operations provided by a GAI transport.
 */
struct gai_transport_operations
{
    gai_transport_free_op free;
};

#ifdef __cplusplus
}
#endif

#endif // __LIBGAI_TRANSPORT_H__
