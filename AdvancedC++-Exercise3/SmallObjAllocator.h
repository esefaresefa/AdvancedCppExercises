#pragma once

#include "MMConfig.h"
#include "FixedAllocator.h"
#include<vector>


class SmallObjAllocator
{
public:

	SmallObjAllocator(std::size_t pageSize= CHUNK_SIZE, std::size_t maxObjectSize= MAX_OBJECT_SIZE);

	~SmallObjAllocator();
	
	void* Allocate(std::size_t numBytes);
	
	//crasha per forza TODO
	void Deallocate(void* p, size_t size = 0);

private:

	std::vector<FixedAllocator> _Pool;

	size_t _MaxSmallObjectSize;
};