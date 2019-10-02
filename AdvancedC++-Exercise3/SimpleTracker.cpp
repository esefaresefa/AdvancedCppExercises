#include "SimpleTracker.h"
#include <stdlib.h>


void* SimpleTracker::Allocate(size_t size)
{
	void* allocatedMemory = nullptr;

	// Allocate the requested memory plus a little space for an header
	size_t* ptr = (size_t*)malloc(size + sizeof(size_t));

	// Store the allocated memory size in the sizeof(size_t) bytes before the object
	ptr[0] = size;

	TrackAllocatedBytes(size);

	// Return the memory address after the size, for the real objet
	allocatedMemory = (void*)(&ptr[1]);

	return allocatedMemory;
}


void SimpleTracker::Deallocate(void *ptr)
{
	void* toFree = nullptr;

	// Get the header with the size stored with the allocate function
	size_t *p = (size_t*)ptr;
	size_t size = p[-1];

	// Track the deallocated memory
	TrackDeallocatedBytes(size);

	// Gets the memory address of all the memory allocated
	void *pFree = (void*)(&p[-1]);

	free(toFree);
};


void SimpleTracker::TrackAllocatedBytes(unsigned int byteCount)
{
	_ByteCount += byteCount;
};


void SimpleTracker::TrackDeallocatedBytes(unsigned int byteCount)
{
	_ByteCount -= byteCount;
};
