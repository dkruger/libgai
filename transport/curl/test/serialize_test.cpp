#include <gmock/gmock.h>
#include <curl/curl.h>
#include "libgai/curl/serialize.h"
#include "libgai/assoc_array.h"



class GaiCurlSerializeTest : public ::testing::Test
{
public:
    virtual void SetUp();
    virtual void TearDown();

    struct gai_assoc_array* array;
    CURL* curl;
};



void GaiCurlSerializeTest::SetUp()
{
    array = gai_assoc_array_new();
    curl = curl_easy_init();
}



void GaiCurlSerializeTest::TearDown()
{
    gai_assoc_array_free(array);
    array = NULL;

    curl_easy_cleanup(curl);
    curl = NULL;
}



TEST_F(GaiCurlSerializeTest, serializingAnEmptyArrayReturnsANULLString)
{
    EXPECT_EQ(((char*)NULL), gai_curl_serialize_params(curl, array));
}



TEST_F(GaiCurlSerializeTest, serializingASingleItem)
{
    gai_assoc_array_set(array, "v", "1");

    char* serialized = gai_curl_serialize_params(curl, array);
    EXPECT_STREQ("v=1", serialized);
    free(serialized);
}



TEST_F(GaiCurlSerializeTest, serializingMultipleItems)
{
    gai_assoc_array_set(array, "v", "1");
    gai_assoc_array_set(array, "tid", "UA-XXXXX-Y");
    gai_assoc_array_set(array, "cid", "555");
    gai_assoc_array_set(array, "t", "pageview");
    gai_assoc_array_set(array, "dp", "home");

    char* serialized = gai_curl_serialize_params(curl, array);
    EXPECT_STREQ(
        "v=1&tid=UA-XXXXX-Y&cid=555&t=pageview&dp=home",
        serialized);
    free(serialized);
}



TEST_F(GaiCurlSerializeTest, serialzingUrlEncodesParameterValue)
{
    gai_assoc_array_set(array, "dp", "/home");

    char* serialized = gai_curl_serialize_params(curl, array);
    EXPECT_STREQ(
        "dp=%2Fhome",
        serialized);
    free(serialized);
}



TEST_F(GaiCurlSerializeTest, serialzingUrlEncodesParameterName)
{
    gai_assoc_array_set(array, "a+b", "c");

    char* serialized = gai_curl_serialize_params(curl, array);
    EXPECT_STREQ(
        "a%2Bb=c",
        serialized);
    free(serialized);
}
