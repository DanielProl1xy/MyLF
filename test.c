#include "containers.h"
#include "assert.h"
#include "stdio.h"

extern void mink_test();
extern void dym_test();

int main(void)
{
    mink_test();
    dym_test();

    return 0;
}

void mink_test()
{
    printf("mink_test ----------------- \n");
    size_t size = 256;
    mink_list list = {0};

    assert(list.head == NULL);
    assert(list.size == 0);
    printf("mink_list sucessfully allocated\n");
    printf("mink_append test: \n");

    for(size_t i = 0; i < size; ++i)
    {
        mink_append(&list, i);
        assert(list.size == i + 1);
        assert(mink_get_end(&list)->value == i);
    }

    printf("succesfully appended. Result is: \n");

    mink_node *curr = list.head;    
    while(curr)
    {
        printf("%i, ", curr->value);
        curr = curr->next;
    }
    printf("\n");
    printf("mink_append test finished. \n");

    printf("mink_free test: \n");
    mink_free(&list);
    assert(list.head == NULL);
    assert(list.size == 0);
    assert(mink_get_end(&list) == NULL);
    printf("succesfully freed list. \n");

    printf("mink_insert test: \n");

    for(size_t i = 0; i < 32; ++i)
    {
        mink_append(&list, i);
        assert(list.size == i + 1);
        assert(mink_get_end(&list)->value == i);
    }
    assert(list.size == 32);
    printf("succesfully created list. \n");
    int val = 2023;
    for(size_t i = 0; i < 32; ++i)
    {
        mink_insert(&list, 6, val);
    }

    assert(list.size == 64);
    assert(mink_get_end(&list)->value == 31);
    assert(mink_get(&list, 6)->value == val);
    printf("succesfully inserted. Result is: \n");

    for(size_t i = 0; i < list.size; ++i)
    {
        printf("%i, ", mink_get(&list, i)->value);
    }
    printf("\n");    

    printf("mink_remove test: \n");
    for(size_t i = 0; i < 32; ++i)
    {
        mink_remove(&list, 6);
    }

    for(size_t i = 0; i < list.size; ++i)
    {
        printf("%i ,", mink_get(&list, i)->value);
    }
    printf("\n");
    printf("mink_remove finished.\n");
    mink_free(&list);
    printf("mink_test finished ----------------- \n");

}

void dym_test()
{
    printf("dym_test ----------------- \n");

    printf("dym_alloc test: \n");
    dym_array arr = {0};
    dym_resize(&arr, MIN_SIZE);
    assert(arr.capacity == MIN_SIZE);
    assert(arr.size == 0);
    assert(arr.data != NULL);
    printf("succesfully allocated array with MIN_SIZE\n");
    
    printf("dym_free test: \n");
    dym_free(&arr);
    assert(arr.size == 0);
    assert(arr.capacity == 0);
    printf("succesfullu freed array\n");
    
    printf("dym_alloc_bz 512 test: \n");
    size_t size = 512;
    dym_resize(&arr, size);    
    assert(arr.size == 0);
    assert(arr.capacity == size);
    printf("succesfully allocated array with 512 size\n");

    printf("dym_append test:\n");
    for(size_t i = 0; i < size; ++i)
    {
        int val = i * i;
        dym_append(&arr, val);
        assert(arr.data[i] == val);
        assert(arr.size == i + 1);
    }

    for(size_t i = 0; i < size; ++i)
    {
        printf("%i, ", arr.data[i]);
    }
    printf("\n");
    printf("succesfully appended array with 512 elements\n");
    
    dym_free(&arr);

    printf("dym_insert test:\n");
    size = 32;
    for(size_t i = 0; i < size; i++)
    {
        dym_append(&arr, i);
    }
    printf("sucessfully created array.\n");
    for(size_t i = 0; i < 6; i++)
    {
        dym_insert(&arr, 15, 2023);
    }
    printf("sucessfully inserted. Result is:\n");

    for(size_t i = 0; i < arr.size; ++i)
    {
        printf("%i, ", arr.data[i]);
    }
    printf("\n");
    printf("dym_remove test:\n");
    for(size_t i = 0; i < 6; i++)
    {
        dym_remove(&arr, 15);
    }
    printf("sucessfully removed. Result is:\n");
    for(size_t i = 0; i < arr.size; ++i)
    {
        printf("%i, ", arr.data[i]);
    }
    dym_free(&arr);

    printf("\n");
    printf("dym_test finished ----------------- \n");
}