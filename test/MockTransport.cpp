#include "MockTransport.h"



void NiceMockTransport_free_trampoline(void* context)
{
    if (context) {
        static_cast<NiceMockTransport*>(context)->free(context);
    }
}



struct gai_transport* create_nicemocked_gai_transport(
    NiceMockTransport* mock)
{
    struct gai_transport_operations operations;
    operations.free = NiceMockTransport_free_trampoline;
    return gai_transport_new(operations, mock);
}
