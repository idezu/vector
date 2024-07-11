#pragma once

#include <stdint.h>
#include <stdlib.h>

typedef struct VECMetadata_T
    {
	uint32_t sizeOfType;
	uint32_t nbElements;
	uint32_t poolSize;
    } VECMetadata;

#define POOLSIZE 64

typedef enum VECResult_T
    {
	VEC_SUCCESS,
	VEC_MEMORY_MAP_FAILED,
    } VECResult;


void* create_vecctor(void *elements, uint32_t nbElements, uint32_t sizeOfType);
VECResult add_vecctor_overlap(void** vecctor_void, void* elements, uint32_t nbElements);
VECResult add_vecctor(void** restrict vecctor_void, void* restrict elements, uint32_t nbElements);
VECResult remove_vecctor(void** vecctor_void, size_t id, uint32_t nbElements);
void destroy_vecctor(void* vecctor_void);
[[__gnu__::__pure__]] uint32_t getTypeSize_vecctor(void* vecctor_void);
[[__gnu__::__pure__]] uint32_t getPoolSize_vecctor(void* vecctor_void);
[[__gnu__::__pure__]] uint32_t getSize_vecctor(void* vecctor_void);
