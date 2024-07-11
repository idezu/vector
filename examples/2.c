#include <assert.h>
#include <stdint.h>
#include <stdio.h>
#include <string.h>
#include <vecctor.h>

#define TIMES 10000000

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
		for (size_t i =1; i <= TIMES; i++)
			{
				add_vecctor((void**)&vecctor_int,&i,1);
			}
		printf("helloworld\n");
		remove_vecctor((void**)&vecctor_int, 900, 90);
		printf("{");
		for (size_t i =0; i < TIMES-90; i++)
			{
				//printf("%d,",vecctor_int[i]);
			}
		printf("}\n");
		//assert(TIMES == getSize_vecctor(vecctor_int));
		printf("vecctor->size\t\t = %u\n",getSize_vecctor(vecctor_int));
		printf("vecctor->poolSize\t = %u vs %lu\n",getPoolSize_vecctor(vecctor_int),((TIMES*sizeof(int))/POOLSIZE)*POOLSIZE+POOLSIZE);
		printf("vecctor->typeSize\t = %u\n",getTypeSize_vecctor(vecctor_int));
		assert(sizeof(int) == getTypeSize_vecctor(vecctor_int));
		destroy_vecctor(vecctor_int);
		return 0;
	}
