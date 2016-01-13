#ifndef __LIBGAI_TEST_MOCKTRANSPORT_H__
#define __LIBGAI_TEST_MOCKTRANSPORT_H__
#include <gmock/gmock.h>
#include "libgai/transport.h"



/**
 * A simple transport object which can be mocked to make testing easier
 */
class MockTransport
{
public:
    MOCK_METHOD2(free, void(struct gai_transport* transport, void* context));
};

/**
 * A typedef for making a NiceMock of the mock transport
 */
typedef ::testing::NiceMock<MockTransport> NiceMockTransport;

/**
 * Trampoline function for NiceMockTransport::free()
 */
void NiceMockTransport_free_trampoline(
    struct gai_transport* transport,
    void* context);

/**
 * Creates a GAI transport instance using gai_transport_new(), providing the
 * @a mock transport as the transport implementation
 */
struct gai_transport* create_nicemocked_gai_transport(
    NiceMockTransport* transport);

#endif // __LIBGAI_TEST_MOCKTRANSPORT_H__
