#include <gmock/gmock.h>
#include "MockTransport.h"
#include "libgai/tracker.h"
#include "libgai/error.h"
#include "libgai/hit.h"
#include "libgai/assoc_array.h"



class GaiTrackerTest : public ::testing::Test
{
public:
    virtual void SetUp();
    virtual void TearDown();

    struct gai_tracker* tracker;
    NiceMockTransport* transport_impl;
    struct gai_transport* transport;
    static const char* tracking_id;
    static const char* client_id;
};

const char* GaiTrackerTest::tracking_id = "UA-XXXX-Y";
const char* GaiTrackerTest::client_id = "35009a79-1a05-49d7-b876-2b884d0f825b";



void GaiTrackerTest::SetUp()
{
    transport_impl = new NiceMockTransport();
    transport = create_nicemocked_gai_transport(transport_impl);
    tracker = gai_tracker_new(tracking_id, client_id, transport);
}



void GaiTrackerTest::TearDown()
{
    gai_tracker_free(tracker);
    tracker = NULL;
    gai_transport_free(transport);
    transport = NULL;
    delete transport_impl;
    transport_impl = NULL;
}



TEST_F(GaiTrackerTest, aNewInstanceShouldNotBeNull)
{
    EXPECT_TRUE(tracker != NULL);
}



TEST_F(GaiTrackerTest, theTrackingIdIsACopyOfTheInput)
{
    EXPECT_NE(tracking_id, gai_tracking_id(tracker));
    EXPECT_STREQ(tracking_id, gai_tracking_id(tracker));
}



TEST_F(GaiTrackerTest, theClientIdIsACopyOfTheInput)
{
    EXPECT_NE(client_id, gai_client_id(tracker));
    EXPECT_STREQ(client_id, gai_client_id(tracker));
}



TEST_F(GaiTrackerTest, shouldSendParametersToConfiguredServer)
{
    const char* test_url = "http://example.com/some/endpoint";
    EXPECT_CALL(*transport_impl, post(::testing::StrEq(test_url),
                                      ::testing::_,
                                      ::testing::_))
        .Times(1);

    gai_tracker_set_server(tracker, test_url);
    gai_send(tracker, NULL);
}



TEST_F(GaiTrackerTest, shouldRefuseToSendAPayloadThatIsTooLarge)
{
    size_t serialized_len = 16*1024;
    char* serialized = static_cast<char*>(malloc(serialized_len));
    memset(serialized, 'a', serialized_len);
    serialized[serialized_len-1] = '\0';
    EXPECT_CALL(*transport_impl, serialize(::testing::_,
                                           ::testing::_))
        .WillOnce(::testing::Return(strdup(serialized)));

    int ret = gai_send(tracker, NULL);

    EXPECT_EQ(GAI_ERR_HIT_TOO_BIG, ret);
    free(serialized);
}



TEST_F(GaiTrackerTest, shouldSerializeTheParametersBeingSent)
{
    const char* serialized = "v=1&b=abcd&name=blak";
    ON_CALL(*transport_impl, serialize(::testing::_,
                                       ::testing::_))
        .WillByDefault(::testing::Return(strdup(serialized)));
    EXPECT_CALL(*transport_impl, post(::testing::_,
                                      ::testing::StrEq(serialized),
                                      ::testing::_))
        .Times(1);

    gai_send(tracker, NULL);
}



MATCHER_P2(AssocArrayHasEntry, key, value, "")
{
    const char* array_val = gai_assoc_array_get(arg, key);
    if ((array_val == NULL) || (value == NULL)) {
        return (array_val == value);
    }
    return strcmp(array_val, value) == 0;
}



TEST_F(GaiTrackerTest, shouldAddVersionWhenSendingAHit)
{
    EXPECT_CALL(*transport_impl, serialize(AssocArrayHasEntry("v", "1"),
                                           ::testing::_))
        .Times(1);

    gai_send_hit(tracker, gai_hit_new(GAI_HIT_EVENT));
}



TEST_F(GaiTrackerTest, shouldAddTrackingIdWhenSendingAHit)
{
    EXPECT_CALL(*transport_impl, serialize(AssocArrayHasEntry("tid", tracking_id),
                                           ::testing::_))
        .Times(1);

    gai_send_hit(tracker, gai_hit_new(GAI_HIT_EVENT));
}



TEST_F(GaiTrackerTest, shouldAddClientIdWhenSendingAHit)
{
    EXPECT_CALL(*transport_impl, serialize(AssocArrayHasEntry("cid", client_id),
                                           ::testing::_))
        .Times(1);

    gai_send_hit(tracker, gai_hit_new(GAI_HIT_EVENT));
}
