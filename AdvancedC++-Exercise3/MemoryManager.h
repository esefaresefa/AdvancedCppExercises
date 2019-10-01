#pragma once

#include "SmallObject.h"
#include "SimpleTracker.h"
#include <iostream>



#ifdef USE_MM_ALLOC

// Defining types
typedef char tChar;
typedef uint32_t tU32;


// Defining function helpers
#define MMNEW(size, type, desc)				MM_NEW(size, type, desc, __FILE__, __LINE__)
#define MMNEWA(size, type, desc)			MM_NEW_A(size, type, desc, __FILE__, __LINE__)
#define MMDELETE(prt, size, type, desc)		MM_DELETE(ptr, size, type, desc, __FILE__, __LINE__)
#define MMDELETEA(prt, size, type, desc)	MM_DELETE_A(ptr, size, type, desc, __FILE__, __LINE__)
#define MMALLOC(ptr, size, type, desc)		MM_MALLOC(ptr, size, type, desc, __FILE__, __LINE__)
#define MMFREE(ptr, size, type, desc)		MM_FREE(ptr, size, type, desc, __FILE__, __LINE__)


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


void MM_FREE(void* ptr, tU32 size, tU32 alloctype, const tChar* desc, const tChar* file, tU32 line)
{
	if (MAX_OBJECT_SIZE >= size)
	{
		// use Simple Tracker Allocator
		SmallObjectAllocator::GetInstance()->Deallocate(ptr, size);
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


void MM_DELETE(void* ptr, size_t size, tU32 alloctype, const tChar* desc, const tChar* file, tU32 line)
{
	MM_FREE(ptr, size, 0, desc, file, line);
}


void MM_DELETE_A(void* ptr, size_t size, tU32 alloctype, const tChar* desc, const tChar* file, tU32 line)
{
	MM_FREE(ptr, size, 0, desc, file, line);
}


void* operator new(size_t size)
{
	return MMNEW(size, 0, "");
}

void* operator new[](size_t size)
{
	return MMNEWA(size, 0, "");
}

void operator delete(void* ptr, size_t size)
{
	MMDELETE(ptr, size, 0, "");
}

void operator delete[](void* ptr, size_t size)
{
	MMDELETEA(ptr, size, 0, ""); 
}


#endif // USE_MM_ALLOC
