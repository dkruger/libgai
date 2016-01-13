#ifndef __LIBGAI_CURL_TRANSPORT_H__
#define __LIBGAI_CURL_TRANSPORT_H__

#ifdef __cplusplus
extern "C" {
#endif

// Forward declarations
struct gai_transport;



/**
 * Create a new GAI transport instance, to free use gai_transport_free()
 *
 * The transport will use the implementation-specific @a operations which make
 * use of the implementtion-specific @a context
 *
 * The ownership of of @a context is assumed to pass to the transport and the
 * associated data should be freed in the implementation's free operation.
 */
struct gai_transport* gai_curl_transport_new();

#ifdef __cplusplus
}
#endif

#endif // __LIBGAI_CURL_TRANSPORT_H__
