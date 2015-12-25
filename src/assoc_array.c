#include "libgai/assoc_array.h"
#include <stdlib.h>
#include <string.h>



// Define the gai_assoc_array struct, its contents are private
struct gai_assoc_array_node {
    struct gai_assoc_array_node* next;
    char* key;
    char* value;
};

struct gai_assoc_array {
    struct gai_assoc_array_node* head;
};



struct gai_assoc_array_node* _gai_assoc_array_node_new(
    const char* key,
    const char* value)
{
    struct gai_assoc_array_node* node = malloc(
        sizeof(struct gai_assoc_array_node));
    if (node == NULL) {
        return node;
    }
    node->next = NULL;
    if (key != NULL) {
        node->key = strdup(key);
    } else {
        node->key = NULL;
    }
    if (value != NULL) {
        node->value = strdup(value);
    } else {
        node->value = NULL;
    }
    return node;
}



void _gai_assoc_array_node_free(struct gai_assoc_array_node* node)
{
    free(node->key);
    free(node->value);
    free(node);
}



struct gai_assoc_array* gai_assoc_array_new()
{
    struct gai_assoc_array* array = malloc(sizeof(struct gai_assoc_array));
    if (array == NULL) {
        return array;
    }
    array->head = NULL;
    return array;
}



void gai_assoc_array_free(struct gai_assoc_array* array)
{
    if (array == NULL) {
        return;
    }
    struct gai_assoc_array_node* iterator = array->head;
    while (iterator != NULL) {
        struct gai_assoc_array_node* next_iterator = iterator->next;
        _gai_assoc_array_node_free(iterator);
        iterator = next_iterator;
    }
}



int _gai_assoc_array_find(
    struct gai_assoc_array* array,
    const char* key,
    struct gai_assoc_array_node** last)
{
    // This is a helper function to find a node with the given key
    for (*last = array->head; *last != NULL; *last = (*last)->next) {
        if (((*last)->key == key) ||
            ((*last)->key && (strcmp(key, (*last)->key) == 0))) {
            return 0;
        }
        if ((*last)->next == NULL) {
            return -1;
        }
    }
    return -1;
}



void gai_assoc_array_set(
    struct gai_assoc_array* array,
    const char* key,
    const char* value)
{
    // If this is the first entry, create the head node and return
    if (array->head == NULL) {
        array->head = _gai_assoc_array_node_new(key, value);
        return;
    }

    // Find the place in the array to put the value
    struct gai_assoc_array_node* iterator = NULL;
    if (_gai_assoc_array_find(array, key, &iterator) == 0) {
        // We found an existing entry in the list, overwrite the value
        free(iterator->value);
        if (value != NULL) {
            iterator->value = strdup(value);
        } else {
            iterator->value = NULL;
        }
    } else {
        // The iterator is pointing to the end of the array, we append the item
        iterator->next = _gai_assoc_array_node_new(key, value);
    }
}



const char* gai_assoc_array_get(
    struct gai_assoc_array* array,
    const char* key)
{
    struct gai_assoc_array_node* iterator = NULL;
    if (_gai_assoc_array_find(array, key, &iterator) == 0) {
        return iterator->value;
    }
    return NULL;
}
