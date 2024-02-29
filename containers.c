#include "containers.h"
#include "assert.h"
#include "string.h"

#ifdef DYM_ARRAY_IMPLEMENTATION

	void dym_free(dym_array *array)
	{
		free(array->data);
		array->capacity = 0;
		array->size = 0;
		array->data = NULL;
	}

	void dym_resize(dym_array *array, size_t size)
	{
		array->data = realloc(array->data, size * sizeof(VALUE_TYPE));
		array->capacity = size;
	}

	void dym_append(dym_array *array, VALUE_TYPE value)
	{
		if(array->data == NULL) dym_resize(array, MIN_SIZE);
		
		if(array->size >= array->capacity)	dym_resize(array, array->capacity * 2);

		array->data[array->size] = value;
		array->size += 1;
	}

	void dym_remove(dym_array *array, size_t id)
	{
		for(size_t i = id; i < array->size; ++i)
		{
			if(i >= id)
			{
				if(i + 1 < array->size)
				{
					array->data[i] = array->data[i + 1];
				}
			}
		}
		array->size -= 1;
	}

	void dym_insert(dym_array *array, size_t pos, VALUE_TYPE value)
	{
		if(array->size >= array->capacity - 1) dym_resize(array, array->capacity * 2);

		memmove(array->data + pos, array->data + pos - 1, array->capacity - pos + 1);
		array->data[pos] = value;
		array->size += 1;
	}

#endif // DYM_ARRAY_IMPLEMENTATION

#ifdef MINK_LIST_IMPLEMENTATION

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
			free(curr);
			curr = next;
		}
		list->size = 0;
		list->head = NULL;
	}

	inline mink_node *mink_next(mink_node *current)
	{
		return current->next;
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

		free(next);
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
