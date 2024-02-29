# **My Little Framework** [aka. MyLF]
## What's this?
This is a small project, created with recreational and educational purposes. Here I've implemented default for computer-science dynamic array and linked list. Implementation and API pretty simple and straightforward. 

I've properly tested all feateures this project provides, and it works pretty good. Additionally, I've checked my code for memory-leaks using Valgrind - my code doesn't create memory-leaks. :D

## Features
- Dynamic array
- Linked list

## Usage
### 1. Build it!
*IDK if it's going to work within other unix systems - I didn't try it. Hopefully it is*

**Linux OS** 

Use snippet below to compile ```./build/containers.so``` library file:
```cmd
git clone https://github.com/DanielProl1xy/MyLF.git
./build/build.bash
```
After that, you can compile test:
```cmd
clang -g test.c -L./build -o ./build/test -Wl,-rpath=$(pwd)/build -l:containers.so
.build/test
```
**Windows OS**
```cmd
git clone https://github.com/DanielProl1xy/MyLF.git
./build/build.bat
```
After that, you can compile test:
```cmd
gcc -g test.c -o build\test -Lbuild\ -l:containers.so
build\test.exe
```

### 2. Code it!

**Dynamic array** aka dym_array

```C++
#include "containers.h"
#include "stdio.h"

int main()
{
    dym_array arr = {0};

    for(size_t i = 0; i < 32; i++)
    {
        dym_append(&arr, i * i);
    }

    dym_remove(&arr, 16);
    dym_insert(&arr, 16, 0);

    for(size_t i = 0; i < arr.size; ++i)
    {
        printf("%i, ", arr.data[i]);
    }

    dym_free(arr);

    return 0;
}
```

**Linked list** aka mink_list
```C++ 
#include "containers.h"
#include "stdio.h"

int main()
{
    mink_list list = {0};

    for(size_t i = 0; i < 32; ++i)
    {
        mink_append(&list, i);
    }
    mink_insert(&list, 5, 30);
    mink_remove(&list, 6);

    mink_node *node = list->head;

    while(node)
    {
        printf("%i\n", node->value);
        node = node->next;
    }

    mink_free(list);

    return 0;
}
```

### 3. Compile your program!
**Linux OS** 
```cmd
clang -g yourprogram.c -L./lib -o ./build/test -Wl,-rpath=$(pwd)/lib -l:containers.so
./yourprogram
```
**Windows OS**
```cmd
gcc -g yourprogram.c -o yourprogram -Llib\ -l:containers.so
yourprogram.exe
```
### **MyLF API**
### Dynamic Array API

Initializes dym_array structure in heap and returs pointer to it
```C
inline dym_array *dym_init();
```
Allocates array of given [size] in heap for given [array]
```C
void dym_alloc(dym_array *array, size_t size);
```
Expands dym_array with given delta. Result size is [array->size + delta]
```C
void dym_expand(dym_array *array, size_t delta);
```
Returns value of [array] at position [id]
```C
inline int dym_get(dym_array *array, size_t id);
```
Sets value of [array] at position [id] with [value]
```C
inline void dym_set(dym_array *array, size_t id, VALUE_TYPE value);
```
Frees array
```C
void dym_free(dym_array *array);
```
Appends as last element to [array] given [value]
```C
void dym_append(dym_array *array, VALUE_TYPE value);
```
Removes element at position [id] and moves all elements by right hand at 1 step to left
```C
void dym_remove(dym_array *array, size_t id);
```
Inserts element at position [id] with [value] and moves all elements by right hand at 1 step to right
```C
void dym_insert(dym_array *array, size_t pos, VALUE_TYPE value);
```
Copies values from right dym_array to right dym_array
```C
void dym_copy(dym_array *from, dym_array *to);
```

### Linked List API

Allocates mink_list structure within heap memory and returns pointer to it.
```C
mink_list *mink_alloc();
```
Allocates mink_node structure within heap memory and returns pointer to it
```C
mink_node *mink_node_alloc();
```
 Frees heap memory by given mink_list pointer
```C
void mink_free(mink_list* list);
```
 Frees heap memory by given mink_node pointer
```C
void mink_free_node(mink_node* list);
```
 Casts __mink_node pointer to mink_node structure pointer
```C
inline mink_node *mink_convert(__mink_node *node);
```
 Returns next node of current mink_node
```C
inline mink_node *mink_next(mink_node *current);
```
 Returns pointer to the  end node of given mink_list 
```C
mink_node *mink_get_end(mink_list *list);
```
Returns pointer to the mink_node with given [id] of given list
```C
mink_node *mink_get(mink_list *list, size_t id);
```
Sets value of node by given [id] with given [value]
```C
void mink_set(mink_list *list, size_t id, VALUE_TYPE value);
```
Appends new node to the end of given [list] with given [value]
```C
void mink_append(mink_list *list, VALUE_TYPE value);
```
 Inserts node at given position [id] with [value] and moves all elements by right hand at 1 step to right
```C
void mink_insert(mink_list *list, size_t id, VALUE_TYPE value);
```
 Removes node at given position [id] and moves all elements by right hand at 1 step to left
```C
void mink_remove(mink_list *list, size_t id);
```

### 4. Rate it!

I would appreciate any proper information which can help me to imporve my code and programming skills! 