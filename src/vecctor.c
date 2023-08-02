#include <assert.h>
#include <stdlib.h>

#include <vecctor.h>

#include "result.h"

inline Result(void) vector_push_back(struct vector_t *Vector, void *Value)
	{
		struct Error_t error = {0};
		Vector->data = realloc(Vector->data, Vector->size+1 * sizeof(void *));
		if (Vector->data == NULL)
		{
			error.message = "realloc failed";
			error.line = __LINE__;
			error.file = __FILE__;
			goto Quit;
		}
		Vector->data[Vector->size++] = Value;
	Quit:
		return (error.line == 0)? 
			(Result(void)){.type = RESULT_OK} :
			(Result(void)){.error = error, .type = RESULT_ERROR};
	}

inline Result(void) vector_push(struct vector_t* Vector, void* Value, size_t Index)
	{
		void * buffer = Vector->data[Index];
		Vector->data[Index] = Value;
		while (++Index < Vector->size)
			{
				Vector->data[Index] = buffer;
				++Index;
			}
		return vector_push_back(Vector, Vector->data[Index]);
	}

inline Result(void) vector_remove(struct vector_t *Vector, size_t Index)
	{
		struct Error_t error = {0};
		if(Index < Vector->size)
			{
				error.line = __LINE__;
				error.file = __FILE__;
				error.message = "index out of range";
				goto Quit;
			}
		Vector->size--; // the last element is not removed
	Quit:
		return (error.line == 0)? 
			(Result(void)){.type = RESULT_OK}:
			(Result(void)){.error = error,.type=RESULT_ERROR};
	}

inline void vector_free(struct vector_t *Vector)
	{
		free(Vector->data);
		Vector->data = NULL;
	}

inline Result(vector) create_vector()
	{
		return (Result(vector)) {
				.value=(vector) {
					.data = NULL,
					.size = 0,
					.push_back = vector_push_back,
					.push = vector_push,
					.remove = vector_remove,
					.free = vector_free
				},
				.type = RESULT_OK 
			};
	}