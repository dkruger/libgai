#include "libgai/curl/transport.h"
#include "libgai/curl/serialize.h"
#include "libgai/curl/post.h"
#include "libgai/transport.h"
#include <curl/curl.h>
#include <stdlib.h>



// Define the gai_curl_transport_impl struct, its contents are private
struct gai_curl_transport_impl {
    CURL* curl;
};

// Forward declarations for internal helper functions
struct gai_curl_transport_impl* gai_curl_transport_impl_new();

void gai_curl_transport_free(void* context);

char* gai_curl_transport_serialize(
    struct gai_assoc_array* params,
    void* context);

int gai_curl_transport_post(
    const char* url,
    const char* payload,
    void* context);



struct gai_transport* gai_curl_transport_new()
{
    struct gai_transport_operations operations;
    gai_transport_operations_init(&operations);
    operations.free = gai_curl_transport_free;
    operations.serialize = gai_curl_transport_serialize;
    operations.post = gai_curl_transport_post;

    struct gai_curl_transport_impl* curl_impl = gai_curl_transport_impl_new();

    return gai_transport_new(operations, curl_impl);
}



struct gai_curl_transport_impl* gai_curl_transport_impl_new()
{
    struct gai_curl_transport_impl* impl = malloc(
        sizeof(struct gai_curl_transport_impl));

    impl->curl = curl_easy_init();

    return impl;
}



void gai_curl_transport_free(void* context)
{
    struct gai_curl_transport_impl* impl = context;

    curl_easy_cleanup(impl->curl);
    impl->curl = NULL;

    free(impl);
}



char* gai_curl_transport_serialize(
    struct gai_assoc_array* params,
    void* context)
{
    struct gai_curl_transport_impl* impl = context;
    return gai_curl_serialize_params(impl->curl, params);
}



int gai_curl_transport_post(
    const char* url,
    const char* payload,
    void* context)
{
    struct gai_curl_transport_impl* impl = context;
    return gai_curl_post(impl->curl, url, payload);
}
