#ifndef __LIBGAI_CURL_SERIALIZE_H__
#define __LIBGAI_CURL_SERIALIZE_H__
#include <curl/curl.h>

#ifdef __cplusplus
extern "C" {
#endif

// Forward declarations
struct gai_assoc_array;



/**
 * Serializes the given @a params into a POST payload
 *
 * Ownership of the returned string is given to the caller.
 */
char* gai_curl_serialize_params(
    CURL* curl,
    struct gai_assoc_array* params);

#ifdef __cplusplus
}
#endif

#endif // __LIBGAI_CURL_SERIALIZE_H__
