#include "MockTransport.h"



void NiceMockTransport_free_trampoline(void* context)
{
    if (context) {
        static_cast<NiceMockTransport*>(context)->free(context);
    }
}



char* NiceMockTransport_serialize_trampoline(
    struct gai_assoc_array* params,
    void* context)
{
    if (context) {
        return static_cast<NiceMockTransport*>(context)->serialize(
            params, context);
    }
    return NULL;
}



int NiceMockTransport_post_trampoline(
    const char* url,
    const char* payload,
    void* context)
{
    if (context) {
        return static_cast<NiceMockTransport*>(context)->post(
            url, payload, context);
    }
    return -1;
}



struct gai_transport* create_nicemocked_gai_transport(
    NiceMockTransport* mock)
{
    struct gai_transport_operations operations;
    gai_transport_operations_init(&operations);
    operations.free = NiceMockTransport_free_trampoline;
    operations.serialize = NiceMockTransport_serialize_trampoline;
    operations.post = NiceMockTransport_post_trampoline;
    return gai_transport_new(operations, mock);
}
