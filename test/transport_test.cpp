#include <gmock/gmock.h>
#include "libgai/transport.h"
#include "libgai/assoc_array.h"
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



TEST_F(GaiTransportTest, serializingWithATransportShouldDelegateToTheImplementation)
{
    struct gai_assoc_array* array = gai_assoc_array_new();
    EXPECT_CALL(*transport_impl, serialize(::testing::Eq(array),
                                           ::testing::Eq(transport_impl)))
        .Times(1);

    gai_transport_serialize(transport, array);

    gai_assoc_array_free(array);
}



TEST_F(GaiTransportTest, postingWithATransportShouldDelegateToTheImplementation)
{
    const char* test_url = "http://www.example.com";
    const char* test_payload = "a=1&b=2";
    EXPECT_CALL(*transport_impl, post(::testing::Eq(test_url),
                                      ::testing::Eq(test_payload),
                                      ::testing::Eq(transport_impl)))
        .WillOnce(::testing::Return(1234));

    int ret = gai_transport_post(transport, test_url, test_payload);

    EXPECT_EQ(1234, ret);
}
