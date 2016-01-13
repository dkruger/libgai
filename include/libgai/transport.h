#ifndef __LIBGAI_TRANSPORT_H__
#define __LIBGAI_TRANSPORT_H__

#ifdef __cplusplus
extern "C" {
#endif

// Forward declarations
struct gai_transport;
struct gai_transport_operations;
struct gai_assoc_array;



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
 * Serializes the given array of @a params into a single string
 *
 * Ownership of the string is given to the caller.
 */
char* gai_transport_serialize(
    struct gai_transport* transport,
    struct gai_assoc_array* params);



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
 * The serialize() operation for the GAI transport implementation
 *
 * This should serialize the list of @a params and return a string. Ownership
 * of the string is given to the caller.
 */
typedef char* (*gai_transport_serialize_op)(
    struct gai_assoc_array* params,
    void* context);

/**
 * The operations provided by a GAI transport.
 */
struct gai_transport_operations
{
    gai_transport_free_op free;
    gai_transport_serialize_op serialize;
};

/**
 * Initializes an gai_transport_operations to ensure that all the fields are
 * cleared.
 */
void gai_transport_operations_init(
    struct gai_transport_operations* operations);

#ifdef __cplusplus
}
#endif

#endif // __LIBGAI_TRANSPORT_H__
