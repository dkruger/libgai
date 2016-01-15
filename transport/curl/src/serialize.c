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

    size_t newSize = 2; // The '=' and the terminating '\0'
    if (current != NULL) {
        newSize += strlen(current)+1; // We need an '&' separator
    }
    newSize += strlen(escapedName);
    newSize += strlen(escapedValue);

    char* appended = realloc(current, newSize);
    if (current != NULL) {
        snprintf(appended, newSize,
            "%s&%s=%s", appended, escapedName, escapedValue);
    } else {
        snprintf(appended, newSize,
            "%s=%s", escapedName, escapedValue);
    }

    curl_free(escapedName);
    curl_free(escapedValue);
    return appended;
}
