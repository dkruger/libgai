#ifndef __LIBGAI_HIT_EVENT_H__
#define __LIBGAI_HIT_EVENT_H__

#ifdef __cplusplus
extern "C" {
#endif

// Forward declarations
struct gai_hit;



/// The hit paramter name for an event action
extern const char* GAI_HIT_PARAM_EVENT_ACTION;

/// The hit paramter name for an event category
extern const char* GAI_HIT_PARAM_EVENT_CATEGORY;

/// The hit paramter name for an event label
extern const char* GAI_HIT_PARAM_EVENT_LABEL;

/// The hit paramter name for an event action
extern const char* GAI_HIT_PARAM_EVENT_VALUE;



/**
 * Sets the event @a action on the GAI @a hit
 *
 * For an event hit to be meaningful, both the category and action must be set.
 *
 * @return The hit that the action was set on, this is to allow chaning of
 *         parameter set calls.
 */
struct gai_hit* gai_hit_event_set_action(
    const char* action,
    struct gai_hit* hit);

/**
 * Sets the event @a category on the GAI @a hit
 *
 * For an event hit to be meaningful, both the category and action must be set.
 *
 * @return The hit that the category was set on, this is to allow chaning of
 *         parameter set calls.
 */
struct gai_hit* gai_hit_event_set_category(
    const char* category,
    struct gai_hit* hit);

/**
 * Sets the event @a label on the GAI @a hit
 *
 * For an event hit to be meaningful, both the category and action must be set.
 *
 * @return The hit that the label was set on, this is to allow chaning of
 *         parameter set calls.
 */
struct gai_hit* gai_hit_event_set_label(
    const char* label,
    struct gai_hit* hit);

/**
 * Sets the event @a value on the GAI @a hit
 *
 * For an event hit to be meaningful, both the category and action must be set.
 *
 * @return The hit that the value was set on, this is to allow chaning of
 *         parameter set calls.
 */
struct gai_hit* gai_hit_event_set_value(
    long value,
    struct gai_hit* hit);

#ifdef __cplusplus
}
#endif

#endif // __LIBGAI_HIT_EVENT_H__
