#include "libgai/hit.h"
#include "libgai/assoc_array.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>



// Define the extern-ed parameters
const char* GAI_HIT_PARAM_API_VERSION = "v";
const char* GAI_HIT_PARAM_TRACKING_ID = "tid";
const char* GAI_HIT_PARAM_CLIENT_ID = "cid";
const char* GAI_HIT_PARAM_TYPE = "t";



// Define the gai_hit struct, its contents are private
struct gai_hit {
    gai_hit_type type;
    struct gai_assoc_array* parameters;
};

// Forward declarations for internal helper functions
char* _gai_hit_create_indexed_parameter_name(
    const char* name_prefix,
    size_t max_index_length,
    int index);

void _gai_hit_set_indexed_parameter(
    const char* name_prefix,
    size_t max_index_length,
    int index,
    const char* value,
    struct gai_hit* hit);

const char* _gai_hit_type_to_string(gai_hit_type type);



// Custom dimensions and metrics parameters are indexed with a known prefix
static const char* CUSTOM_DIMENSION_PARAMETER_PREFIX = "cd";
static size_t CUSTOM_DIMENSION_MAX_INDEX_LENGTH = 3; // 1-200

static const char* CUSTOM_METRIC_PARAMETER_PREFIX = "cm";
static size_t CUSTOM_METRIC_MAX_INDEX_LENGTH = 3; // 1-200



struct gai_hit* gai_hit_new(gai_hit_type type)
{
    struct gai_hit* hit = malloc(sizeof(struct gai_hit));
    hit->type = type;
    hit->parameters = gai_assoc_array_new();
    return hit;
}



void gai_hit_free(struct gai_hit* hit)
{
    if (hit == NULL) {
        return;
    }
    gai_assoc_array_free(hit->parameters);
    free(hit);
}



gai_hit_type gai_hit_get_type(struct gai_hit* hit)
{
    return hit->type;
}



struct gai_assoc_array* gai_hit_build(struct gai_hit* hit)
{
    struct gai_assoc_array* hit_params = gai_assoc_array_copy(hit->parameters);
    gai_assoc_array_set(
        hit_params, GAI_HIT_PARAM_TYPE, _gai_hit_type_to_string(hit->type));
    return hit_params;
}



struct gai_hit* gai_hit_set_parameter(
    const char* name,
    const char* value,
    struct gai_hit* hit)
{
    gai_assoc_array_set(hit->parameters, name, value);
    return hit;
}



struct gai_hit* gai_hit_set_api_version(
    const char* version,
    struct gai_hit* hit)
{
    return gai_hit_set_parameter(GAI_HIT_PARAM_API_VERSION, version, hit);
}



struct gai_hit* gai_hit_set_tracking_id(
    const char* tracking_id,
    struct gai_hit* hit)
{
    return gai_hit_set_parameter(GAI_HIT_PARAM_TRACKING_ID, tracking_id, hit);
}



struct gai_hit* gai_hit_set_client_id(
    const char* client_id,
    struct gai_hit* hit)
{
    return gai_hit_set_parameter(GAI_HIT_PARAM_CLIENT_ID, client_id, hit);
}



struct gai_hit* gai_hit_set_custom_dimension(
    int index,
    const char* dimension,
    struct gai_hit* hit)
{
    _gai_hit_set_indexed_parameter(
        CUSTOM_DIMENSION_PARAMETER_PREFIX,
        CUSTOM_DIMENSION_MAX_INDEX_LENGTH,
        index,
        dimension,
        hit);
    return hit;
}



struct gai_hit* gai_hit_set_custom_metric(
    int index,
    int metric,
    struct gai_hit* hit)
{
    char value[32];
    snprintf(value, 31, "%d", metric);
    _gai_hit_set_indexed_parameter(
        CUSTOM_METRIC_PARAMETER_PREFIX,
        CUSTOM_METRIC_MAX_INDEX_LENGTH,
        index,
        value,
        hit);
    return hit;
}



void _gai_hit_set_indexed_parameter(
    const char* name_prefix,
    size_t max_index_length,
    int index,
    const char* value,
    struct gai_hit* hit)
{
    char* parameter_name = _gai_hit_create_indexed_parameter_name(
        name_prefix, max_index_length, index);
    gai_hit_set_parameter(parameter_name, value, hit);
    free(parameter_name);
}



char* _gai_hit_create_indexed_parameter_name(
    const char* name_prefix,
    size_t max_index_length,
    int index)
{
    size_t max_param_len = strlen(name_prefix) + max_index_length + 1;
    char* parameter_name = malloc(sizeof(char)*(max_param_len));
    snprintf(
        parameter_name,
        max_param_len,
        "%s%d",
        name_prefix,
        index);
    return parameter_name;
}



const char* _gai_hit_type_to_string(gai_hit_type type)
{
    switch (type) {
        case GAI_HIT_PAGEVIEW: return "pageview";
        case GAI_HIT_SCREENVIEW: return "screenview";
        case GAI_HIT_EVENT: return "event";
        case GAI_HIT_TRANSACTION: return "transaction";
        case GAI_HIT_ITEM: return "item";
        case GAI_HIT_SOCIAL: return "social";
        case GAI_HIT_EXCEPTION: return "exception";
        case GAI_HIT_TIMING: return "timing";
    }
    return "unknown";
}
