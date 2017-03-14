#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "IntVector.h"

IntVector *int_vector_new(size_t initial_capacity)
{
	IntVector *v = malloc(sizeof(IntVector));
	if (v == NULL) {
		return NULL;
	}
	v->data = malloc(initial_capacity * sizeof(int));
	if (v->data == NULL) {
		free(v);
		return NULL;
	}
	v->size = 0;
	v->capacity = initial_capacity;
	return v;
}

IntVector *int_vector_copy(const IntVector *v)
{
	IntVector *c = malloc(sizeof(IntVector));
	if (c == NULL) {
		return NULL;
	}
	c->data = malloc(v->capacity * sizeof(int));
	if (c->data == NULL) {
		free(c);
		return NULL;
	}
	memcpy(c->data, v->data,v->capacity * sizeof(int)); 
	c->size = v->size;
	c->capacity = v->capacity;
	return c;
}

void int_vector_free(IntVector *v)
{	
	free(v->data);
	free(v);
}

int int_vector_get_item(const IntVector *v, size_t index)
{
	if ((index < v->capacity) && (index >= 0)) {
		return v->data[index];
	}
	return 0;
	
}

void int_vector_set_item(IntVector *v, size_t index, int item)
{
	if ((index < v->capacity) && (index >= 0)) {
		v->data[index] = item;
		v->size++;
	}
}

size_t int_vector_get_size(const IntVector *v)
{
	return v->size;
}
 
size_t int_vector_get_capacity(const IntVector *v)
{
	return v->capacity;
}

int int_vector_push_back(IntVector *v, int item)
{	
	if (v->capacity == 0) {
		v->capacity = 1;
	}
	if (v->size < v->capacity) {
			v->data[v->size] = item;
			v->size++;
		}
	else {
		v->capacity = v->capacity * 2;
		v->data = realloc(v->data, v->capacity * sizeof(int));
		if (v->data == NULL) {
			return -1;
		}
		v->data[v->size] = item;
		v->size++;
	}
	return 0;
}

void int_vector_pop_back(IntVector *v)
{	
	if (v->size > 0) {
		v->size--;
		v->data[v->size] = 0;	
	}
}

int int_vector_shrink_to_fit(IntVector *v)
{	
	if (v->capacity > v->size) {
		int *tmp = realloc(v->data, v->size * sizeof(int));
		if (tmp == NULL) {
			return -1;
		}
		v->data = tmp;
	}
	v->capacity = v->size;
	return 0;
}

int int_vector_resize(IntVector *v, size_t new_size)
{
	if (v->size <= new_size) {
		int *tmp = realloc(v->data, new_size * sizeof(int));
		if (tmp == NULL) {
			return -1;
		}
		v->data = tmp;
		for (int i = v->size; i < new_size; i++) {
			v->data[i] = 0;
		}
		v->size = new_size;
	}
	return 0;
}

int int_vector_reserve(IntVector *v, size_t new_capacity)
{
	if (new_capacity > v->capacity) {
		int *tmp = realloc(v->data, new_capacity * sizeof(int));
		if (tmp == NULL) {
			return -1;
		}
		v->data = tmp;	
		v->capacity = new_capacity;
	}
	return 0;
}
