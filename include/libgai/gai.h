#ifndef __LIBGAI_GAI_H__
#define __LIBGAI_GAI_H__

#ifdef __cplusplus
extern "C" {
#endif

// Forward declarations
typedef struct gai_st gai_t;



/**
 * Create a new gai_t with the given context, to free use gai_free()
 *
 * The ownership of context is left to the caller.
 */
gai_t* gai_new(void* context);

/**
 * Frees the @a gai instance.
 */
void gai_free(gai_t* gai);

#ifdef __cplusplus
}
#endif

#endif // __LIBGAI_GAI_H__
