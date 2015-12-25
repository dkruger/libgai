#ifndef __LIBGAI_ASSOC_ARRAY_H__
#define __LIBGAI_ASSOC_ARRAY_H__

#ifdef __cplusplus
extern "C" {
#endif

// Forward declarations
struct gai_assoc_array;



/**
 * Create a new associative array instance, to free use gai_assoc_array_free()
 *
 * This is a simple associative array object suitable for small lists of items.
 */
struct gai_assoc_array* gai_assoc_array_new();

/**
 * Frees the @a array instance.
 *
 * This will free the @a array, along with any values stored in the array.
 */
void gai_assoc_array_free(struct gai_assoc_array* array);

/**
 * Associates the given @a value with the given @a key in the @a array
 *
 * Both @a key and @a value will deeply copied before storing in the @a array.
 *
 * Calling this method with the same @a key will overwrite the previous
 * @a value with the new one. This will free the associated memory.
 */
void gai_assoc_array_set(
    struct gai_assoc_array* array,
    const char* key,
    const char* value);

/**
 * Retrieves the value from the stored in the @a array with the given @a key.
 *
 * If there is no associated value, then NULL will be returned.
 *
 * @return The value associated with the key in the array, or NULL if no value
 *         was found.
 */
const char* gai_assoc_array_get(
    struct gai_assoc_array* array,
    const char* key);

#ifdef __cplusplus
}
#endif

#endif // __LIBGAI_ASSOC_ARRAY_H__

