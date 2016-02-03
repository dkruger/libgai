#ifndef __LIBGAI_HIT_PAGEVIEW_H__
#define __LIBGAI_HIT_PAGEVIEW_H__

#ifdef __cplusplus
extern "C" {
#endif

// Forward declarations
struct gai_hit;



/// The hit paramter name for a pageview title
extern const char* GAI_HIT_PARAM_PAGEVIEW_TITLE;

/// The hit paramter name for a pageview location
extern const char* GAI_HIT_PARAM_PAGEVIEW_LOCATION;

/// The hit paramter name for a pageview page
extern const char* GAI_HIT_PARAM_PAGEVIEW_PAGE;



/**
 * Sets the pageview @a title on the GAI @a hit
 *
 * For a pageview hit to be meaningful the location, page, or both must be set.
 *
 * @return The hit that the title was set on, this is to allow chaning of
 *         parameter set calls.
 */
struct gai_hit* gai_hit_pageview_set_title(
    const char* title,
    struct gai_hit* hit);

/**
 * Sets the pageview @a location on the GAI @a hit
 *
 * For a pageview hit to be meaningful the location, page, or both must be set.
 *
 * @return The hit that the location was set on, this is to allow chaning of
 *         parameter set calls.
 */
struct gai_hit* gai_hit_pageview_set_location(
    const char* location,
    struct gai_hit* hit);

/**
 * Sets the pageview @a page on the GAI @a hit
 *
 * For a pageview hit to be meaningful the location, page, or both must be set.
 *
 * @return The hit that the page was set on, this is to allow chaning of
 *         parameter set calls.
 */
struct gai_hit* gai_hit_pageview_set_page(
    const char* page,
    struct gai_hit* hit);

#ifdef __cplusplus
}
#endif

#endif // __LIBGAI_HIT_PAGEVIEW_H__
