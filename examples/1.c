#include <stddef.h>
#include <stdio.h>
#include <vecctor.h>

int main(void)
	{
		char* vector = (char*)create_vecctor(NULL, 0, sizeof(char));
		char test[] = "hello world";
		VECResult result = add_vecctor((void**)&vector,test,12);
		if (result != VEC_SUCCESS)
			{
				printf("error\n");
			}
		printf("vector\t\t\t = \"%s\"\n",vector);
		printf("vecctor[10]\t\t = '%c'\n",vector[10]);
		printf("vecctor->size\t\t = %u\n",getSize_vecctor(vector));
		printf("vecctor->poolSize\t = %u\n",getPoolSize_vecctor(vector));
		printf("vecctor->typeSize\t = %u\n",getTypeSize_vecctor(vector));
		destroy_vecctor(vector);
		return 0;
	}
