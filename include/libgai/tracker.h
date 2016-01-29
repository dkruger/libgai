#ifndef __LIBGAI_TRACKER_H__
#define __LIBGAI_TRACKER_H__

#ifdef __cplusplus
extern "C" {
#endif

// Forward declarations
struct gai_tracker;
struct gai_transport;



/**
 * The default HTTP host for the GAI tracker
 * @see gai_tracker_set_server()
 */
extern const char* GAI_TRACKER_DEFAULT_HOST;

/**
 * The default HTTP target for the GAI tracker
 * @see gai_tracker_set_server()
 */
extern const char* GAI_TRACKER_DEFAULT_TARGET;



/**
 * Create a new GAI tracker instance, to free use gai_tracker_free()
 *
 * The GAI tracking ID is obtained through the Google Analytics site. The
 * tracker retains a copy of the ID.
 *
 * The GAI client ID is a UUID used to identify the client. If you want to do
 * client tracking over multiple sessions, this should be reatined in the
 * system. @see https://developers.google.com/analytics/devguides/collection/protocol/v1/parameters#cid
 *
 * The transport provided will be used for sending the hit calls. The tracker
 * leaves ownership of the @a transport to the caller.
 *
 * The ownership of context is left to the caller.
 */
struct gai_tracker* gai_tracker_new(
    const char* tracking_id,
    const char* client_id,
    struct gai_transport* transport,
    void* context);

/**
 * Frees the @a tracker instance.
 */
void gai_tracker_free(struct gai_tracker* tracker);

/**
 * Retrieves the tracking id assigned to the tracker instance
 */
const char* gai_tracking_id(struct gai_tracker* tracker);

/**
 * Retrieves the client id assigned to the tracker instance
 */
const char* gai_client_id(struct gai_tracker* tracker);

/**
 * Overrides the default analytics server
 *
 * By default host is www.google-analytics.com and the target is "/collect".
 * By overriding the target to "/debug/collect" for example, the hits can be
 * validated by the Google Analytics server.
 * @see https://developers.google.com/analytics/devguides/collection/protocol/v1/validating-hits
 */
void gai_tracker_set_server(
    struct gai_tracker* tracker,
    const char* host,
    const char* target);

#ifdef __cplusplus
}
#endif

#endif // __LIBGAI_TRACKER_H__
