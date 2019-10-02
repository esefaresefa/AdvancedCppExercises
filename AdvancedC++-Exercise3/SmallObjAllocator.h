#pragma once

#include "MMConfig.h"
#include "FixedAllocator.h"
#include<vector>


class SmallObjAllocator
{
public:

	SmallObjAllocator(std::size_t pageSize, std::size_t maxObjectSize, std::size_t objectAlignSize);
	
	void* Allocate(std::size_t numBytes);
	
	void Deallocate(void* p, size_t size = 0);

private:

	std::vector<FixedAllocator> _Pool;
	
	FixedAllocator* _LastAlloc;
	
	FixedAllocator* _LastDealloc;

	bool TrimExcessMemory(void);

	size_t _MaxSmallObjectSize;

	size_t _ObjectAlignSize;
};