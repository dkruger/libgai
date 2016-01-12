#ifndef __LIBGAI_HIT_H__
#define __LIBGAI_HIT_H__

#ifdef __cplusplus
extern "C" {
#endif

// Forward declarations
struct gai_hit;
struct gai_assoc_array;



/**
 * Enumeration of possible GAI hit types
 */
typedef enum {
    GAI_HIT_PAGEVIEW,
    GAI_HIT_SCREENVIEW,
    GAI_HIT_EVENT,
    GAI_HIT_TRANSACTION,
    GAI_HIT_ITEM,
    GAI_HIT_SOCIAL,
    GAI_HIT_EXCEPTION,
    GAI_HIT_TIMING
} gai_hit_type;



/**
 * Create a new GAI hit instance, to free use gai_hit_free()
 *
 * A hit must be associated with a given @a type. The @a type determines which
 * parameters is expected of it.
 */
struct gai_hit* gai_hit_new(gai_hit_type type);

/**
 * Frees the @a hit instance.
 */
void gai_hit_free(struct gai_hit* hit);

/**
 * Retrieves the type assigned to the given @a hit.
 */
gai_hit_type gai_hit_get_type(struct gai_hit* hit);

/**
 * Builds a map (associated array) of the hit's parameters and values
 *
 * This can be used with the gai_tracker object to send hits.
 */
struct gai_assoc_array* gai_hit_build(struct gai_hit* hit);

/**
 * Sets the parameter on the GAI @a hit to with the given @a name and @a value
 *
 * Calling this method with the same @a name on the same @a hit will overwrite
 * any previously assigned @a value.
 *
 * @return The hit that the parameter was set on, this is to allow chaning of
 *         parameter set calls.
 */
struct gai_hit* gai_hit_set_parameter(
    const char* name,
    const char* value,
    struct gai_hit* hit);

/**
 * Adds a custom @a dimension to the @a hit.
 *
 * Calling this method with the same @a index will overwrite the previous
 * @a dimension with the new one. Refer to http://goo.gl/igziD2 for details on
 * how to set the custom dimensions up.
 *
 * @return The hit that the dimension was set on, this is to allow chaning of
 *         parameter set calls.
 */
struct gai_hit* gai_hit_set_custom_dimension(
    int index,
    const char* dimension,
    struct gai_hit* hit);

/**
 * Adds a custom @a metric to the @a hit.
 *
 * Calling this method with the same @a index will overwrite the previous
 * @a metric with the new one. Refer to http://goo.gl/igziD2 for details on
 * how to set the custom metrics up.
 *
 * @return The hit that the metric was set on, this is to allow chaning of
 *         parameter set calls.
 */
struct gai_hit* gai_hit_set_custom_metric(
    int index,
    int metric,
    struct gai_hit* hit);

#ifdef __cplusplus
}
#endif

#endif // __LIBGAI_HIT_H__
