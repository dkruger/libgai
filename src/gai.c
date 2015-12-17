#include "libgai/gai.h"
#include <stdlib.h>



// Define the gai_t, its contents are private
struct gai_st {
    void* context;
};



gai_t* gai_new(void* context)
{
    gai_t* gai = malloc(sizeof(gai_t));
    gai->context = context;
    return gai;
}



void gai_free(gai_t* gai)
{
    free(gai);
}
