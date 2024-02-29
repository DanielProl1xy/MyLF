#pragma once

#include "stdlib.h"

#define MYLF_CONTAINERS 
#define MYLF_INLINE

// goddamn, change it later, please
typedef int VALUE_TYPE;

#ifndef MIN_SIZE
    #define MIN_SIZE 6
#endif

#ifndef NO_DYM_ARRAY
#define DYM_ARRAY_IMPLEMENTATION

typedef struct
{
    VALUE_TYPE *data;
    size_t size;
    size_t capacity;

} dym_array;


MYLF_CONTAINERS void dym_free(dym_array *array);
// Allocates array of given [size] in heap for given [array]
MYLF_CONTAINERS void dym_resize(dym_array *array, size_t size);
// Expands dym_array with given delta. Result size is [array->size + delta]
MYLF_CONTAINERS void dym_expand(dym_array *array, size_t delta);
// Appends as last element to [array] given [value]
MYLF_CONTAINERS void dym_append(dym_array *array, VALUE_TYPE value);
// Removes element at position [id] and moves all elements by right hand at 1 step to left
MYLF_CONTAINERS void dym_remove(dym_array *array, size_t id);
// Inserts element at position [id] with [value] and moves all elements by right hand at 1 step to right
MYLF_CONTAINERS void dym_insert(dym_array *array, size_t pos, VALUE_TYPE value);

#endif // DYM_ARRAY

#ifndef NO_MINK_LIST
#define MINK_LIST_IMPLEMENTATION

typedef void __mink_node;

typedef struct
{
    __mink_node *next;
    VALUE_TYPE value;

}  mink_node;

typedef struct 
{
    mink_node *head;
    size_t size;
    
} mink_list;

// Allocates mink_node structure within heap memory and returns pointer to it
MYLF_CONTAINERS mink_node *mink_node_alloc(void);
// Frees heap memory by given mink_list pointer
MYLF_CONTAINERS void mink_free(mink_list *list);
// Returns next node of current mink_node
MYLF_CONTAINERS MYLF_INLINE mink_node *mink_next(mink_node *current);
// Returns pointer to the  end node of given mink_list 
MYLF_CONTAINERS mink_node *mink_get_end(mink_list *list);
// Returns pointer to the mink_node with given [id] of given list
MYLF_CONTAINERS mink_node *mink_get(mink_list *list, size_t id);
// Sets value of node by given [id] with given [value]
MYLF_CONTAINERS void mink_set(mink_list *list, size_t id, VALUE_TYPE value);
// Appends new node to the end of given [list] with given [value]
MYLF_CONTAINERS void mink_append(mink_list *list, VALUE_TYPE value);
// Inserts node at given position [id] with [value] and moves all elements by right hand at 1 step to right
MYLF_CONTAINERS void mink_insert(mink_list *list, size_t id, VALUE_TYPE value);
// Removes node at given position [id] and moves all elements by right hand at 1 step to left
MYLF_CONTAINERS void mink_remove(mink_list *list, size_t id);

#endif // MINK_LIST
