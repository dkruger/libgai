#include <gmock/gmock.h>
#include "libgai/hit.h"



class GaiHitTest : public ::testing::Test
{
public:
    virtual void SetUp();
    virtual void TearDown();

    struct gai_hit* hit;
};



void GaiHitTest::SetUp()
{
    hit = gai_hit_new(GAI_HIT_EVENT);
}



void GaiHitTest::TearDown()
{
    gai_hit_free(hit);
    hit = NULL;
}



TEST_F(GaiHitTest, aNewInstanceShouldNotBeNull)
{
    EXPECT_TRUE(hit != NULL);
}



TEST_F(GaiHitTest, theHitTypeCanBeRetrieved)
{
    EXPECT_EQ(GAI_HIT_EVENT, gai_hit_get_type(hit));
}
