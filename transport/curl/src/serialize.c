#include "libgai/curl/serialize.h"
#include "libgai/assoc_array.h"
#include <stdlib.h>
#include <string.h>



// Forward declarations for internal helper functions
char* append_parameter(
    CURL* curl,
    char* current,
    const char* name,
    const char* value);

char* create_initial_escaped_parameter(
    const char* escapedName,
    const char* escapedValue);

char* append_escaped_parameter(
    char* current,
    const char* escapedName,
    const char* escapedValue);



char* gai_curl_serialize_params(
    CURL* curl,
    struct gai_assoc_array* params)
{
    char* serializedPost = NULL;

    struct gai_assoc_array_iterator* iterator = NULL;
    for (iterator = gai_assoc_array_begin(params);
         iterator != NULL;
         iterator = gai_assoc_array_next(iterator)) {
        // Append each parameter to the string
        serializedPost = append_parameter(
            curl,
            serializedPost,
            gai_assoc_array_get_key(iterator),
            gai_assoc_array_get_value(iterator));
    }

    return serializedPost;
}



char* append_parameter(
    CURL* curl,
    char* current,
    const char* name,
    const char* value)
{
    char* escapedName = curl_easy_escape(curl, name, 0);
    char* escapedValue = curl_easy_escape(curl, value, 0);

    char* appended = NULL;
    if (current == NULL) {
        appended = create_initial_escaped_parameter(escapedName, escapedValue);
    } else {
        appended = append_escaped_parameter(current, escapedName, escapedValue);
    }

    curl_free(escapedName);
    curl_free(escapedValue);
    return appended;
}



char* create_initial_escaped_parameter(
    const char* escapedName,
    const char* escapedValue)
{
    // Create a string <name>=<value>\0
    size_t initialSize = strlen(escapedName) + strlen(escapedValue) + 2;
    char* parameter = malloc(initialSize);
    snprintf(parameter, initialSize, "%s=%s", escapedName, escapedValue);
    return parameter;
}



char* append_escaped_parameter(
    char* current,
    const char* escapedName,
    const char* escapedValue)
{
    // Create a string <current>&<name>=<value>\0
    size_t currentLen = strlen(current);
    size_t appendSize = strlen(escapedName) + strlen(escapedValue) + 3;
    char* appended = realloc(current, appendSize+currentLen);
    snprintf(appended+currentLen, appendSize,
        "&%s=%s", escapedName, escapedValue);
    return appended;
}
