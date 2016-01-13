#include "libgai/transport.h"
#include <stdlib.h>



// Define the gai_transport struct, its contents are private
struct gai_transport {
    struct gai_transport_operations operations;
    void* context;
};



struct gai_transport* gai_transport_new(
    struct gai_transport_operations operations,
    void* context)
{
    struct gai_transport* transport = malloc(sizeof(struct gai_transport));
    transport->operations = operations;
    transport->context = context;
    return transport;
}



void gai_transport_free(struct gai_transport* transport)
{
    if (transport && transport->operations.free) {
        // Run the implementation free which should free the context
        transport->operations.free(transport->context);
        transport->context = NULL;
    }
    free(transport);
}



char* gai_transport_serialize(
    struct gai_transport* transport,
    struct gai_assoc_array* params)
{
    if (transport && transport->operations.serialize) {
        // Run the implementation serialiation
        return transport->operations.serialize(params, transport->context);
    }
    return NULL;
}



void* gai_transport_get_context(struct gai_transport* transport)
{
    return transport->context;
}



void gai_transport_operations_init(struct gai_transport_operations* operations)
{
    operations->free = NULL;
    operations->serialize = NULL;
}
