#pragma once

#include "MMConfig.h"
#include "FixedAllocator.h"
#include<vector>


class SmallObjAllocator
{
public:

	SmallObjAllocator(size_t pageSize= CHUNK_SIZE,size_t maxObjectSize= MAX_OBJECT_SIZE);

	~SmallObjAllocator();
	
	void* Allocate(size_t numBytes);
	
	void Deallocate(void* p, size_t size);

private:

	FixedAllocator _Pool[MAX_OBJECT_SIZE];

	size_t _MaxSmallObjectSize;
};