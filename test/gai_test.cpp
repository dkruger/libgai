#include <gmock/gmock.h>
#include "libgai/gai.h"



class GaiTest : public ::testing::Test
{
public:
    virtual void SetUp();
    virtual void TearDown();

    gai_t* gai;
};



void GaiTest::SetUp()
{
    gai = gai_new(NULL);
}



void GaiTest::TearDown()
{
    gai_free(gai);
    gai = NULL;
}



TEST_F(GaiTest, aNewInstanceShouldNotBeNull)
{
    EXPECT_TRUE(gai != NULL);
}
