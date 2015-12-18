#include "libgai/tracker.h"
#include <stdlib.h>
#include <string.h>



// Define the gai_tracker_t, its contents are private
struct gai_tracker_st {
    char* tracking_id;
    char* client_id;
    void* context;
};



gai_tracker_t* gai_tracker_new(
    const char* tracking_id,
    const char* client_id,
    void* context)
{
    gai_tracker_t* tracker = malloc(sizeof(gai_tracker_t));
    tracker->tracking_id = strdup(tracking_id);
    tracker->client_id = strdup(client_id);
    tracker->context = context;
    return tracker;
}



void gai_tracker_free(gai_tracker_t* tracker)
{
    free(tracker->tracking_id);
    free(tracker->client_id);
    free(tracker);
}



const char* gai_tracking_id(gai_tracker_t* tracker)
{
    return tracker->tracking_id;
}



const char* gai_client_id(gai_tracker_t* tracker)
{
    return tracker->client_id;
}
