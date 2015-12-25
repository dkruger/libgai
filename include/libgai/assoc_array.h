#ifndef __LIBGAI_ASSOC_ARRAY_H__
#define __LIBGAI_ASSOC_ARRAY_H__

#ifdef __cplusplus
extern "C" {
#endif

// Forward declarations
struct gai_assoc_array;
struct gai_assoc_array_iterator;



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

/**
 * Retrieves an iterator which points to the beginning of the given @a array
 */
struct gai_assoc_array_iterator* gai_assoc_array_begin(
    struct gai_assoc_array* array);

/**
 * Frees the array @a iterator instance.
 */
void gai_assoc_array_iterator_free(struct gai_assoc_array_iterator* iterator);

/**
 * Retrieves the key for the item pointed to by the given @a iterator
 *
 * If the iterator is invalid, NULL will be returned. Notice, though, that NULL
 * is a valid key.
 */
const char* gai_assoc_array_get_key(
    struct gai_assoc_array_iterator* iterator);

/**
 * Retrieves the value for the item pointed to by the given @a iterator
 *
 * If the iterator is invalid, NULL will be returned. Notice, though, that NULL
 * is a valid value.
 */
const char* gai_assoc_array_get_value(
    struct gai_assoc_array_iterator* iterator);

/**
 * Moves the @a iterator to the next item in the array
 *
 * When the at the end of the list, a NULL value is returned, and the
 * @a iterator is free-ed with gai_assoc_array_iterator_free().
 *
 * @return The iterator, identical to the value that is passed in, or NULL when
 *         the end of the array is reached.
 */
struct gai_assoc_array_iterator* gai_assoc_array_next(
    struct gai_assoc_array_iterator* iterator);

#ifdef __cplusplus
}
#endif

#endif // __LIBGAI_ASSOC_ARRAY_H__

