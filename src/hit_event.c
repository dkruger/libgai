#include "libgai/hit_event.h"
#include "libgai/hit.h"
#include <stdlib.h>
#include <stdio.h>



const char* GAI_HIT_PARAM_EVENT_ACTION = "ea";
const char* GAI_HIT_PARAM_EVENT_CATEGORY = "ec";
const char* GAI_HIT_PARAM_EVENT_LABEL = "el";
const char* GAI_HIT_PARAM_EVENT_VALUE = "ev";



struct gai_hit* gai_hit_event_set_action(
    const char* action,
    struct gai_hit* hit)
{
    return gai_hit_set_parameter(GAI_HIT_PARAM_EVENT_ACTION, action, hit);
}



struct gai_hit* gai_hit_event_set_category(
    const char* category,
    struct gai_hit* hit)
{
    return gai_hit_set_parameter(GAI_HIT_PARAM_EVENT_CATEGORY, category, hit);
}



struct gai_hit* gai_hit_event_set_label(
    const char* label,
    struct gai_hit* hit)
{
    return gai_hit_set_parameter(GAI_HIT_PARAM_EVENT_LABEL, label, hit);
}



struct gai_hit* gai_hit_event_set_value(
    long value,
    struct gai_hit* hit)
{
    const int value_len = snprintf(NULL, 0, "%ld", value);
    const int buffer_len = value_len+1;
    char* buffer = malloc(buffer_len);
    snprintf(buffer, buffer_len, "%ld", value);
    gai_hit_set_parameter(GAI_HIT_PARAM_EVENT_VALUE, buffer, hit);
    free(buffer);
    return hit;
}
