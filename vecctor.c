#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

#include <string.h>
#include <vecctor.h>

[[__gnu__::__pure__]] // enable futher optimization on functions the doesn't mutate states and return only a value
uint32_t getSize_vecctor(void* vecctor_void)
	{
		return (((VECMetadata*)(vecctor_void))-1)->nbElements;
	}

[[__gnu__::__pure__]]
uint32_t getPoolSize_vecctor(void* vecctor_void)
	{
		return (((VECMetadata*)(vecctor_void))-1)->poolSize;
	}

[[__gnu__::__pure__]]
uint32_t getTypeSize_vecctor(void* vecctor_void)
	{
		return (((VECMetadata*)(vecctor_void))-1)->sizeOfType;
	}

/**
 * @brief add an element to a vector
 * 
 * @param vecctor_void a pointer to the vecctor
 * @param elements elements to add
 * @param nbElements number of elements to add
 * @return VECResult 
 */
VECResult add_vecctor(void** restrict vecctor_void, void* restrict elements, uint32_t nbElements)
	{
		if (nbElements == 0)
			{
				return VEC_SUCCESS;
			}
		// get the metadata
		VECMetadata* vecctor = (VECMetadata*)*vecctor_void;
		vecctor--;

		// get the poolsize necessary for the data
		uint32_t poolsize = (((nbElements+vecctor->nbElements)*vecctor->sizeOfType)/POOLSIZE)*POOLSIZE+POOLSIZE;

		if (poolsize > vecctor->poolSize)
			{
				vecctor = (VECMetadata*)realloc(vecctor,poolsize+sizeof(VECMetadata));
				if (vecctor == NULL)
					{
						return VEC_MEMORY_MAP_FAILED;
					}
				*vecctor_void = (void*) (vecctor+1);
				vecctor->poolSize = poolsize;
			}

		char* vecctor_char = (char*)*vecctor_void;

		memcpy(vecctor_char+vecctor->sizeOfType*vecctor->nbElements,elements,nbElements*vecctor->sizeOfType);
		vecctor->nbElements += nbElements;

		return VEC_SUCCESS;
	}

/**
 * @brief remove an element from a vecctor
 * 
 * @param vecctor_void a pointer to the vecctor
 * @param id the if of the element to remove
 * @param nbElements number of elements to remove
 * @return VECResult 
 */
VECResult remove_vecctor(void** vecctor_void, size_t id, uint32_t nbElements)
	{
		if (nbElements == 0)
			{
				return VEC_SUCCESS;
			}
		// get the metadata
		VECMetadata* vecctor = (VECMetadata*)*vecctor_void;
		vecctor--;

		char* vecctor_char = (char*)*vecctor_void;

		memmove(vecctor_char+vecctor->sizeOfType*(id-1),vecctor_char+vecctor->sizeOfType*(id-1+nbElements),nbElements*vecctor->sizeOfType);
		vecctor->nbElements -= nbElements;

		// get the poolsize necessary for the new data size
		uint32_t poolsize = (((vecctor->nbElements)*vecctor->sizeOfType)/POOLSIZE)*POOLSIZE+POOLSIZE;

		if (poolsize < vecctor->poolSize)
			{
				vecctor = (VECMetadata*)realloc(vecctor,poolsize+sizeof(VECMetadata));
				if (vecctor == NULL)
					{
						return VEC_MEMORY_MAP_FAILED;
					}
				*vecctor_void = (void*) (vecctor+1);
				vecctor->poolSize = poolsize;
			}

		return VEC_SUCCESS;
	}

/**
 * @brief add an element to a vector, this function accept ovelapping data
 * 
 * @param vecctor_void a pointer to the vecctor
 * @param elements elements to add
 * @param nbElements number of elements to add
 * @return VECResult 
 */
VECResult add_vecctor_overlap(void** vecctor_void, void* elements, uint32_t nbElements)
	{
		if (nbElements == 0)
		{
		    return VEC_SUCCESS;
		}
		// get the metadata
		VECMetadata* vecctor = (VECMetadata*)*vecctor_void;
		vecctor--;

		// get the poolsize necessary for the data
		uint32_t poolsize = (((nbElements+vecctor->nbElements)*vecctor->sizeOfType)/POOLSIZE)*POOLSIZE+POOLSIZE;

		if (poolsize > vecctor->poolSize)
		    {
			vecctor = (VECMetadata*)realloc(vecctor,poolsize+sizeof(VECMetadata));
			if (vecctor == NULL)
				{
					return VEC_MEMORY_MAP_FAILED;
				}
			*vecctor_void = (void*) (vecctor+1);
			vecctor->poolSize = poolsize;
		    }

		char* vecctor_char = (char*)*vecctor_void;

		memcpy(vecctor_char+vecctor->sizeOfType*vecctor->nbElements,elements,nbElements*vecctor->sizeOfType);
		vecctor->nbElements += nbElements;

		return VEC_SUCCESS;
	}

/**
 * @brief Create a vecctor object
 * 
 * @param elements elements to put in the newly created vecctor
 * @param nbElements number of elements to put in the newly created vecctor
 * @param sizeOfType size of the type
 * @return void* 
 */
void* create_vecctor(void *elements, uint32_t nbElements, uint32_t sizeOfType)
	{
		uint32_t poolsize = ((nbElements*sizeOfType)/POOLSIZE)*POOLSIZE+POOLSIZE;
		VECMetadata* vecctor = (VECMetadata*)malloc(poolsize+sizeof(VECMetadata));
		if (vecctor == NULL)
			{
				return NULL;
			}
		vecctor->sizeOfType = sizeOfType;
		vecctor->poolSize = poolsize;
		vecctor->nbElements = nbElements;
		void* vecctor_void = (void*) (vecctor+1);
		add_vecctor(&vecctor_void,elements,nbElements);
		return vecctor_void;
	}

/**
 * @brief Destroy a vecctor object
 * 
 * @param vecctor_void 
 */
void destroy_vecctor(void* vecctor_void)
	{
		VECMetadata* vecctor = (VECMetadata*)vecctor_void;
		vecctor--;
		free(vecctor);
	}
