#include "libgai/curl/post.h"



int gai_curl_post(
    CURL* curl,
    const char* url,
    const char* payload)
{
    curl_easy_setopt(curl, CURLOPT_URL, url);
    if (payload) {
        curl_easy_setopt(curl, CURLOPT_COPYPOSTFIELDS, payload);
    }

    CURLcode res = curl_easy_perform(curl);

    if (res == CURLE_OK) {
        return 0;
    }
    return res;
}
