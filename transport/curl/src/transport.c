#include "libgai/curl/transport.h"
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



struct gai_transport* gai_curl_transport_new()
{
    struct gai_transport_operations operations;
    operations.free = gai_curl_transport_free;

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
