#ifndef VECTOR_H
#define VECTOR_H

#define DEFAULT_GROWTH_FACTOR 2 
#define DEFAULT_CAPACITY 10

#include <stddef.h>
#include "result.h"

typedef struct vector_t
	{
		void **data;
		size_t size;
		Result(void)(*push_back)(struct vector_t *Vector, void *Value);
		Result(void)(*push)(struct vector_t *Vector, void *Value, size_t Index);
		Result(void)(*remove)(struct vector_t *Vector, size_t Index);
		void (*free)(struct vector_t *Vector);
	} vector;

ResultDEF(vector);

Result(void) vector_push_back(vector *Vector, void *Value);


Result(void) vector_push(vector* Vector, void* Value, size_t Index);


Result(void) vector_remove(vector *Vector, size_t Index);
void vector_free(vector *Vector);

Result(vector) create_vector();

#endif