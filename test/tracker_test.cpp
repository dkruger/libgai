#include <gmock/gmock.h>
#include "libgai/tracker.h"



class GaiTrackerTest : public ::testing::Test
{
public:
    virtual void SetUp();
    virtual void TearDown();

    struct gai_tracker* tracker;
    static const char* tracking_id;
    static const char* client_id;
};

const char* GaiTrackerTest::tracking_id = "UA-XXXX-Y";
const char* GaiTrackerTest::client_id = "35009a79-1a05-49d7-b876-2b884d0f825b";



void GaiTrackerTest::SetUp()
{
    tracker = gai_tracker_new(tracking_id, client_id, NULL);
}



void GaiTrackerTest::TearDown()
{
    gai_tracker_free(tracker);
    tracker = NULL;
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
