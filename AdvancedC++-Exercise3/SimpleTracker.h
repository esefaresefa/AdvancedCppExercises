#pragma once

#include "Singleton.h"


class SimpleTracker 
{
public:

	void* Allocate(size_t size);

	void Deallocate(void *ptr);

private:

	unsigned int _ByteCount = 0;

	void TrackAllocatedBytes(unsigned int byteCount);

	void TrackDeallocatedBytes(unsigned int byteCount);
};


typedef Singleton<SimpleTracker> SimpleTrackerAllocator;