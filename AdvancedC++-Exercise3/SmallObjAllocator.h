#pragma once

#include "Config.h"
#include "FixedAllocator.h"
#include<vector>


class SmallObjAllocator
{
public:

	SmallObjAllocator(size_t chunkSize = CHUNK_SIZE, size_t maxObjectSize = MAX_OBJECT_SIZE) {};
	
	void* Allocate(size_t numBytes) { return nullptr; };
	
	void Deallocate(void* p, size_t size = 0) {};

private:

	std::vector<FixedAllocator> _Pool;
	
	FixedAllocator* _LastAlloc;
	
	FixedAllocator* _LastDealloc;
};