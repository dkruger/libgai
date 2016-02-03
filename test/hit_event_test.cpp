#include <gmock/gmock.h>
#include "libgai/hit.h"
#include "libgai/hit_event.h"
#include "libgai/assoc_array.h"



class GaiHitEventTest : public ::testing::Test
{
public:
    virtual void SetUp();
    virtual void TearDown();

    struct gai_hit* hit;
};



void GaiHitEventTest::SetUp()
{
    hit = gai_hit_new(GAI_HIT_EVENT);
}



void GaiHitEventTest::TearDown()
{
    gai_hit_free(hit);
    hit = NULL;
}



TEST_F(GaiHitEventTest, theHitValueShouldBeConvertedToAString)
{
    gai_hit_event_set_value(11235813, hit);

    struct gai_assoc_array* params = gai_hit_build(hit);
    const char* value =gai_assoc_array_get(params, GAI_HIT_PARAM_EVENT_VALUE);

    EXPECT_STREQ("11235813", value);
    gai_assoc_array_free(params);
}
