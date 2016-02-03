#include "libgai/hit_pageview.h"
#include "libgai/hit.h"



const char* GAI_HIT_PARAM_PAGEVIEW_TITLE = "title";
const char* GAI_HIT_PARAM_PAGEVIEW_LOCATION = "location";
const char* GAI_HIT_PARAM_PAGEVIEW_PAGE = "page";



struct gai_hit* gai_hit_pageview_set_title(
    const char* title,
    struct gai_hit* hit)
{
    return gai_hit_set_parameter(GAI_HIT_PARAM_PAGEVIEW_TITLE, title, hit);
}



struct gai_hit* gai_hit_pageview_set_location(
    const char* location,
    struct gai_hit* hit)
{
    return gai_hit_set_parameter(
        GAI_HIT_PARAM_PAGEVIEW_LOCATION, location, hit);
}



struct gai_hit* gai_hit_pageview_set_page(
    const char* page,
    struct gai_hit* hit)
{
    return gai_hit_set_parameter(GAI_HIT_PARAM_PAGEVIEW_PAGE, page, hit);
}
