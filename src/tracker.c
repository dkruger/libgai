#include "libgai/tracker.h"
#include <stdlib.h>
#include <string.h>



// Define the gai_tracker struct, its contents are private
struct gai_tracker {
    char* tracking_id;
    char* client_id;
    char* url;
    struct gai_transport* transport;
};



const char* GAI_TRACKER_DEFAULT_SERVER_URL = "http://www.google-analytics.com/collect";
const int GAI_TRACKER_MAX_HIT_PAYLOAD_SIZE = 8192; // 8k limit on hits



struct gai_tracker* gai_tracker_new(
    const char* tracking_id,
    const char* client_id,
    struct gai_transport* transport)
{
    struct gai_tracker* tracker = malloc(sizeof(struct gai_tracker));
    tracker->tracking_id = strdup(tracking_id);
    tracker->client_id = strdup(client_id);
    tracker->transport = transport;
    tracker->url = strdup(GAI_TRACKER_DEFAULT_SERVER_URL);
    return tracker;
}



void gai_tracker_free(struct gai_tracker* tracker)
{
    free(tracker->tracking_id);
    free(tracker->client_id);
    free(tracker->url);
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
    const char* url)
{
    free(tracker->url);
    tracker->url = strdup(url);
}
