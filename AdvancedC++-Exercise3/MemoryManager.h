#pragma once

#include "SmallObject.h"
#include "SimpleTracker.h"
#include <iostream>



#ifdef USE_MM_ALLOC

// Defining types
typedef char tChar;
typedef uint32_t tU32;


// Defining function helpers
#define MMNEW(size, type, desc)			MM_NEW(size, type, desc, __FILE__, __LINE__)
#define MMNEWA(size, type, desc)		MM_NEW_A(size, type, desc, __FILE__, __LINE__)
#define MMDELETE(ptr, type, desc)		MM_DELETE(ptr, type, desc, __FILE__, __LINE__)
#define MMDELETEA(ptr, type, desc)		MM_DELETE_A(ptr, type, desc, __FILE__, __LINE__)
#define MMALLOC(ptr, size, type, desc)	MM_MALLOC(ptr, size, type, desc, __FILE__, __LINE__)
#define MMFREE(ptr, type, desc)			MM_FREE(ptr, type, desc, __FILE__, __LINE__)


static size_t count = 0;
void TraceAlloc(tU32 size, tU32 alloctype, const tChar* desc, const tChar* file, tU32 line)
{
	count += size;
}


void TraceDealloc(tU32 size, tU32 alloctype, const tChar* desc, const tChar* file, tU32 line)
{
	count -= size;
}


void* MM_MALLOC(tU32 size, tU32 alloctype, const tChar* desc, const tChar* file, tU32 line)
{
	void* allocMem;

	if (MAX_OBJECT_SIZE >= size)
	{
		// use Simple Tracker Allocator
		allocMem = SmallObjectAllocator::GetInstance()->Allocate(size);
	}
	else
	{
		// use Small Object Allocator
		allocMem = SimpleTrackerAllocator::GetInstance()->Allocate(size);
	}

	TraceAlloc(size, alloctype, desc, file, line); // ?

	return allocMem;
};


void MM_FREE(void* ptr, tU32 alloctype, const tChar* desc, const tChar* file, tU32 line)
{
	size_t size = 4; // TODO geto from map indirizzo-size / indirizzo-desc ? / indirizzo-line ?

	if (MAX_OBJECT_SIZE >= size)
	{
		// use Simple Tracker Allocator
		SmallObjectAllocator::GetInstance()->Deallocate(ptr);
	}
	else
	{
		// use Small Object Allocator
		SimpleTrackerAllocator::GetInstance()->Deallocate(ptr);
	}

	TraceDealloc(size, alloctype, desc, file, line);
};


void* MM_NEW(size_t size, tU32 alloctype, const tChar* desc, const tChar* file, tU32 line)
{
	return MM_MALLOC(size, alloctype, desc, file, line);
}


void* MM_NEW_A(size_t size, tU32 alloctype, const tChar* desc, const tChar* file, tU32 line)
{
	return MM_MALLOC(size, alloctype, desc, file, line);
}


void MM_DELETE(void* ptr, tU32 alloctype, const tChar* desc, const tChar* file, tU32 line)
{
	MM_FREE(ptr, 0, desc, file, line);
}


void MM_DELETE_A(void* ptr, tU32 alloctype, const tChar* desc, const tChar* file, tU32 line)
{
	MM_FREE(ptr, 0, desc, file, line);
}


void* operator new(size_t size)
{
	return MMNEW(size, 0, "");
}

void* operator new[](size_t size)
{
	return MMNEWA(size, 0, "");
}

void operator delete(void* ptr)
{
	MMDELETE(ptr, 0, "");
}

void operator delete[](void* ptr)
{
	MMDELETEA(ptr, 0, ""); 
}


#endif // USE_MM_ALLOC
