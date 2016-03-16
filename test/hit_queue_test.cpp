#include <gmock/gmock.h>
#include "libgai/hit_queue.h"
#include "libgai/hit.h"
#include "MockHitQueue.h"



class GaiHitQueueTest : public ::testing::Test
{
public:
    virtual void SetUp();
    virtual void TearDown();

    NiceMockHitQueue* hit_queue_impl;
    struct gai_hit_queue* hit_queue;
};



void GaiHitQueueTest::SetUp()
{
    hit_queue_impl = new NiceMockHitQueue();
    hit_queue = create_nicemocked_gai_hit_queue(hit_queue_impl);
}



void GaiHitQueueTest::TearDown()
{
    gai_hit_queue_free(hit_queue);
    hit_queue = NULL;
    delete hit_queue_impl;
    hit_queue_impl = NULL;
}



TEST_F(GaiHitQueueTest, aNewInstanceShouldNotBeNull)
{
    EXPECT_TRUE(hit_queue != NULL);
}



TEST_F(GaiHitQueueTest, freeingAHitQueueShouldDelegateToTheImplementation)
{
    EXPECT_CALL(*hit_queue_impl, free(::testing::Eq(hit_queue_impl)))
        .Times(1);

    gai_hit_queue_free(hit_queue);
    hit_queue = NULL;
}



TEST_F(GaiHitQueueTest, aHitQueuesPayloadOverheadDependsOnTheImplementation)
{
    ON_CALL(*hit_queue_impl, payload_overhead(::testing::Eq(hit_queue_impl)))
        .WillByDefault(::testing::Return(112233));

    size_t overhead = gai_hit_queue_payload_overhead(hit_queue);

    EXPECT_EQ(112233, overhead);
}



TEST_F(GaiHitQueueTest, enqueuingAHitDelegatesToTheImplementation)
{
    struct gai_hit* hit = gai_hit_new(GAI_HIT_PAGEVIEW);
    EXPECT_CALL(*hit_queue_impl, enqueue(
            ::testing::Eq(hit),
            ::testing::Eq(hit_queue_impl)))
        .WillOnce(::testing::Return(112233));

    int retcode = gai_hit_queue_enqueue(hit_queue, hit);
    gai_hit_free(hit);

    EXPECT_EQ(112233, retcode);
}
