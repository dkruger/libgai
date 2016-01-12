#include <gmock/gmock.h>
#include "libgai/hit.h"
#include "libgai/assoc_array.h"



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



TEST_F(GaiHitTest, buildingAHitShouldIncludeTheHitType)
{
    struct gai_assoc_array* params = gai_hit_build(hit);

    EXPECT_STREQ("event", gai_assoc_array_get(params, "t"));
}



TEST_F(GaiHitTest, buildingAHitShouldIncludeAllAddedParameters)
{
    gai_hit_set_parameter("name", "bob", hit);
    gai_hit_set_parameter("place", "moon", hit);

    struct gai_assoc_array* params = gai_hit_build(hit);

    EXPECT_STREQ("bob", gai_assoc_array_get(params, "name"));
    EXPECT_STREQ("moon", gai_assoc_array_get(params, "place"));
}



TEST_F(GaiHitTest, buildingAHitShouldIncludeCustomMetrics)
{
    gai_hit_set_custom_metric(1, 100, hit);
    gai_hit_set_custom_metric(200, 42, hit);

    struct gai_assoc_array* params = gai_hit_build(hit);

    EXPECT_STREQ("100", gai_assoc_array_get(params, "cm1"));
    EXPECT_STREQ("42", gai_assoc_array_get(params, "cm200"));
}



TEST_F(GaiHitTest, buildingAHitShouldIncludeCustomDimensions)
{
    gai_hit_set_custom_dimension(1, "foo", hit);
    gai_hit_set_custom_dimension(200, "bar", hit);

    struct gai_assoc_array* params = gai_hit_build(hit);

    EXPECT_STREQ("foo", gai_assoc_array_get(params, "cd1"));
    EXPECT_STREQ("bar", gai_assoc_array_get(params, "cd200"));
}
