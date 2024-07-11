#include <assert.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <vecctor.h>

#undef NDEBUG

int main()
	{
		char* vector = (char*)create_vecctor(NULL, 0, sizeof(char));
		assert(vector != NULL);
		char test[] = "hello world";
		size_t testlen = strlen(test);
		VECResult result = add_vecctor((void**)&vector,test,(uint32_t)testlen);
		assert(result != VEC_MEMORY_MAP_FAILED);
		assert(result == VEC_SUCCESS);
		for (size_t i = 0; i < testlen ; i++)
			{
				assert(vector[i] == test[i]);
			}

		assert(testlen == getSize_vecctor(vector));
		assert(POOLSIZE == getPoolSize_vecctor(vector));
		assert(sizeof(char) == getTypeSize_vecctor(vector));
		destroy_vecctor(vector);

		int* vecctor_int = (int*)create_vecctor(NULL, 0, sizeof(int));
		assert(vecctor_int != NULL);
		for (size_t i =0; i < 1000; i++)
			{
				add_vecctor((void**)&vecctor_int,&i,1);
			}
		assert(1000 == getSize_vecctor(vecctor_int));
		assert(((1000*sizeof(int))/POOLSIZE)*POOLSIZE+POOLSIZE == getPoolSize_vecctor(vecctor_int));
		assert(sizeof(int) == getTypeSize_vecctor(vecctor_int));
		destroy_vecctor(vecctor_int);
		return 0;
	}
