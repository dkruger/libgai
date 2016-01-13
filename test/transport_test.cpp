#include <gmock/gmock.h>
#include "libgai/transport.h"
#include "MockTransport.h"



class GaiTransportTest : public ::testing::Test
{
public:
    virtual void SetUp();
    virtual void TearDown();

    NiceMockTransport* transport_impl;
    struct gai_transport* transport;
};



void GaiTransportTest::SetUp()
{
    transport_impl = new NiceMockTransport();
    transport = create_nicemocked_gai_transport(transport_impl);
}



void GaiTransportTest::TearDown()
{
    gai_transport_free(transport);
    transport = NULL;
    delete transport_impl;
    transport_impl = NULL;
}



TEST_F(GaiTransportTest, aNewInstanceShouldNotBeNull)
{
    EXPECT_TRUE(transport != NULL);
}



TEST_F(GaiTransportTest, freeingATransportShouldDelegateToTheImplementation)
{
    EXPECT_CALL(*transport_impl, free(::testing::Eq(transport_impl)))
        .Times(1);

    gai_transport_free(transport);
    transport = NULL;
}
