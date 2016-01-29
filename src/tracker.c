#include "libgai/tracker.h"
#include <stdlib.h>
#include <string.h>



// Define the gai_tracker struct, its contents are private
struct gai_tracker {
    char* tracking_id;
    char* client_id;
    char* http_host;
    char* http_target;
    struct gai_transport* transport;
    void* context;
};



const char* GAI_TRACKER_DEFAULT_HOST = "www.google-analytics.com";
const char* GAI_TRACKER_DEFAULT_TARGET = "/collect";



struct gai_tracker* gai_tracker_new(
    const char* tracking_id,
    const char* client_id,
    struct gai_transport* transport,
    void* context)
{
    struct gai_tracker* tracker = malloc(sizeof(struct gai_tracker));
    tracker->tracking_id = strdup(tracking_id);
    tracker->client_id = strdup(client_id);
    tracker->transport = transport;
    tracker->context = context;
    tracker->http_host = strdup(GAI_TRACKER_DEFAULT_HOST);
    tracker->http_target = strdup(GAI_TRACKER_DEFAULT_TARGET);
    return tracker;
}



void gai_tracker_free(struct gai_tracker* tracker)
{
    free(tracker->tracking_id);
    free(tracker->client_id);
    free(tracker->http_host);
    free(tracker->http_target);
    free(tracker);
}



const char* gai_tracking_id(struct gai_tracker* tracker)
{
    return tracker->tracking_id;
}



const char* gai_client_id(struct gai_tracker* tracker)
{
    return tracker->client_id;
}



void gai_tracker_set_server(
    struct gai_tracker* tracker,
    const char* host,
    const char* target)
{
    free(tracker->http_host);
    free(tracker->http_target);
    tracker->http_host = strdup(host);
    tracker->http_target = strdup(target);
}
