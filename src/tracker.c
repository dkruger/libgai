#include "libgai/tracker.h"
#include "libgai/transport.h"
#include "libgai/assoc_array.h"
#include "libgai/hit.h"
#include "libgai/error.h"
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



int gai_tracker_post(struct gai_tracker* tracker, const char* payload)
{
    return gai_transport_post(
        tracker->transport,
        tracker->url,
        payload);
}



int gai_send(
    struct gai_tracker* tracker,
    struct gai_assoc_array* parameters)
{
    char* payload = gai_transport_serialize(tracker->transport, parameters);
    // Google Analytics has a limit on the max size of a hit
    // @see https://developers.google.com/analytics/devguides/collection/protocol/v1/reference
    if (payload && (strlen(payload) > GAI_TRACKER_MAX_HIT_PAYLOAD_SIZE)) {
        free(payload);
        return GAI_ERR_HIT_TOO_BIG;
    }
    gai_tracker_post(tracker, payload);
    free(payload);
    return 0;
}



int gai_send_hit(struct gai_tracker* tracker, struct gai_hit* hit)
{
    // Assign the required tracker-level parameters
    gai_hit_set_parameter("v", "1", hit);
    gai_hit_set_parameter("tid", tracker->tracking_id, hit);
    gai_hit_set_parameter("cid", tracker->client_id, hit);

    struct gai_assoc_array* hit_params = gai_hit_build(hit);
    int ret = gai_send(tracker, hit_params);
    gai_assoc_array_free(hit_params);
    gai_hit_free(hit);
    return ret;
}
