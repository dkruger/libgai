#include "libgai/tracker.h"
#include <stdlib.h>
#include <string.h>



// Define the gai_tracker struct, its contents are private
struct gai_tracker {
    char* tracking_id;
    char* client_id;
    void* context;
};



struct gai_tracker* gai_tracker_new(
    const char* tracking_id,
    const char* client_id,
    void* context)
{
    struct gai_tracker* tracker = malloc(sizeof(struct gai_tracker));
    tracker->tracking_id = strdup(tracking_id);
    tracker->client_id = strdup(client_id);
    tracker->context = context;
    return tracker;
}



void gai_tracker_free(struct gai_tracker* tracker)
{
    free(tracker->tracking_id);
    free(tracker->client_id);
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
