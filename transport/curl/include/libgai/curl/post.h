#ifndef __LIBGAI_CURL_POST_H__
#define __LIBGAI_CURL_POST_H__
#include <curl/curl.h>

#ifdef __cplusplus
extern "C" {
#endif

/**
 * POST the given @a payload to the given @a url
 */
int gai_curl_post(
    CURL* curl,
    const char* url,
    const char* payload);

#ifdef __cplusplus
}
#endif

#endif // __LIBGAI_CURL_POST_H__
