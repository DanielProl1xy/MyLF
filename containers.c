#include "containers.h"
#include "assert.h"


#ifdef DYM_ARRAY_IMPLEMENTATION

    inline dym_array *dym_init(void)
    {
        return (dym_array *) malloc(sizeof(dym_array));;
    }    

    void dym_alloc(dym_array *array, size_t size)
    {
        array->begin = (int *) malloc(sizeof(int) * size);
        array->end = array->begin + (size - 1);
        array->size = size;
        array->last = 0;
    }

    void dym_expand(dym_array *array, size_t delta)
    {
        assert(delta > 0);

        size_t new_size = array->size + delta;
        dym_array *tmp = dym_init();
        dym_alloc(tmp, array->size);

        dym_copy(array, tmp);        
        dym_free(array);
        dym_alloc(array, new_size);

        dym_copy(tmp, array);
        dym_free(tmp);
        free(tmp);
    }

    inline int dym_get(dym_array *array, size_t id)
    {
        assert(id < array->size);

        return array->begin[id];
    }

    inline void dym_set(dym_array *array, size_t id, VALUE_TYPE value)
    {
        assert(array->begin);
        array->begin[id] = value;
    }

    void dym_free(dym_array *array)
    {
        if(array != NULL)
        {
            if(array->begin != NULL)
            {
                free(array->begin);
            }
            array->size = 0;
            array->last = 0;
            array->begin = NULL;
            array->end = NULL;
        }

    }

    void dym_append(dym_array *array, VALUE_TYPE value)
    {
        if(array->begin == NULL) dym_alloc(array, MIN_SIZE);
        
        if(array->last == array->size) dym_expand(array, MIN_SIZE);

        dym_set(array, array->last, value);

        array->last += 1;
    }

    void dym_remove(dym_array *array, size_t id)
    {
        for(size_t i = 0; i < array->size; ++i)
        {
            if(i >= id)
            {
                if(i + 1 < array->size)
                    dym_set(array, i, dym_get(array, i + 1));
            }
        }
        array->last -= 1;
    }

    void dym_insert(dym_array *array, size_t pos, VALUE_TYPE value)
    {
        if(array->last > array->size - 1) dym_expand(array, MIN_SIZE);

        dym_array *tmp = dym_init();
        dym_copy(array, tmp);
        array->last += 1;

        size_t y = pos;
        for(size_t i = 0; i < array->last; ++i)
        {
            if(i == pos) 
            {
                dym_set(array, i, value);
            }
            if(i > pos)
            {
                dym_set(array, i, dym_get(tmp, y++));
            }
        }
        dym_free(tmp);
        free(tmp);
    }

    void dym_copy(dym_array *from, dym_array *to)
    {
        assert(from && to);

        if(to->begin == NULL)
        {
            dym_alloc(to, from->size);
        }
        if(to->size < from->size)
        {
            dym_alloc(to, from->size);
        }

        assert(to->begin);
        for(size_t i = 0; i < from->last; i++)
        {
            dym_set(to, i, dym_get(from, i));
        }

        to->last = from->last;
    }

#endif // DYM_ARRAY_IMPLEMENTATION

#ifdef MINK_LIST_IMPLEMENTATION

    inline mink_list *mink_alloc(void)
    {
        mink_list *ls = (mink_list *) malloc(sizeof(mink_list));
        ls->head = NULL;
        ls->size = 0;
        return ls;
    }

    inline mink_node *mink_node_alloc(void)
    {
        mink_node *nd = (mink_node *) malloc(sizeof(mink_node));
        nd->next = NULL;
        return nd;
    }

    void mink_free(mink_list* list)
    {
        mink_node *curr = list->head;
        mink_node *next = curr;
        while(next)
        {
            next = curr->next;
            mink_free_node(curr);
            curr = next;
        }
        list->size = 0;
        list->head = NULL;
    }

    void mink_free_node(mink_node* node)
    {
        if(node == NULL) return;
        free(node);
    }

    inline mink_node *mink_convert(__mink_node *node)
    {
        return (mink_node *)node;
    }

    inline mink_node *mink_next(mink_node *current)
    {
        return mink_convert(current->next);
    }

    mink_node *mink_get_end(mink_list *list)
    {
        if(list->size < 2)
        {
            return list->head;
        }

        mink_node *n = list->head;

        while(n->next != NULL)
        {
            n = n->next;
        }

        return n;
    }

    void mink_append(mink_list *list, VALUE_TYPE value)
    {
        assert(list != NULL);

        if(list->head == NULL)
        {
            list->head = mink_node_alloc();
            list->head->next = NULL;
            list->head->value = value;
        }
        else
        {
            mink_node *end = mink_get_end(list);
            mink_node *n = mink_node_alloc();
            n->value = value;
            end->next = n;
        }

        list->size += 1;
        
    }

    void mink_insert(mink_list *list, size_t id, VALUE_TYPE value)
    {
        assert(id < list->size);

        mink_node *insert = mink_node_alloc();
        if(id == 0)
        {
            insert->value = value;
            insert->next = list->head;
            list->head = insert;
        }
        else
        {
            mink_node *prev = mink_get(list, id - 1);
            mink_node *next = prev->next;

            insert->next = next;
            prev->next = insert;
            
            insert->value = value;

        }        
        list->size += 1;
    }

    void mink_remove(mink_list *list, size_t id)
    {
        mink_node *rm = mink_get(list, id);
        mink_node *next = rm->next;
        rm->next = next->next;
        rm->value = next->value;

        list->size -= 1;

        mink_free_node(next);
    }

    
    mink_node *mink_get(mink_list *list, size_t id)
    {
        assert(id < list->size);

        mink_node *n = list->head;
        for(size_t i = 0; i < id; ++i)
        {
            if(n->next)
            {
                n = n->next;
            }
            else return NULL;
        }
        return n;
    }

    void mink_set(mink_list *list, size_t id, VALUE_TYPE value)
    {
        assert(id < list->size); 
        mink_get(list, id)->value = value;
    }


#endif // MINK_LIST_IMPLEMENTATION