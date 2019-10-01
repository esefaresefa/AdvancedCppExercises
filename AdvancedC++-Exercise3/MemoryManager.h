#pragma once

#include <iostream>


#ifdef USE_MM_ALLOC

// Defining types
typedef char tChar;
typedef uint32_t tU32;


// Defining function helpers
#define MMNEW(SIZE, TYPE, DESC)		MM_NEW(SIZE, TYPE, DESC, __FILE__, __LINE__)
#define MMNEWA(SIZE, TYPE, DESC)	MM_NEW_A(SIZE, TYPE, DESC, __FILE__, __LINE__)
#define MMDELETE(PTR)				MM_DELETE(PTR, __FILE__, __LINE__)
#define MMDELETEA(PTR)				MM_DELETE_A(PTR, __FILE__, __LINE__)
#define MMALLOC(SIZE, TYPE, DESC)	MM_MALLOC(SIZE, TYPE, DESC, __FILE__, __LINE__)
#define MMFREE(SIZE, TYPE, DESC)	MM_FREE(SIZE, TYPE, DESC, __FILE__, __LINE__)
// #define MMREALLOC(PTR, SIZE)		MM_REALLOC(PTR, SIZE, __FILE__, __LINE__)


static size_t count = 0;
void TraceAlloc(tU32 Size, tU32 AllocType, const tChar* Desc, const tChar* File, tU32 Line)
{
	count += Size;
}


void TraceDealloc(tU32 Size, tU32 AllocType, const tChar* Desc, const tChar* File, tU32 Line)
{
	count -= Size;
}


void* MM_MALLOC(tU32 Size, tU32 AllocType, const tChar* Desc, const tChar* File, tU32 Line)
{
	void* allocMem;

	if (MAX_OBJECT_SIZE >= Size)
	{
		allocMem = nullptr;
	}
	else
	{
		allocMem = malloc(Size);
	}

	TraceAlloc(Size, AllocType, Desc, File, Line);

	return allocMem;
};


void MM_FREE(void* ptr)
{
	free(ptr);
};


void* MM_NEW(size_t Size, tU32 AllocType, const tChar* Desc, const tChar* File, tU32 Line)
{
	return MM_MALLOC(Size, AllocType, Desc, File, Line);
}


void* MM_NEW_A(size_t Size, tU32 AllocType, const tChar* Desc, const tChar* File, tU32 Line)
{
	return MM_MALLOC(Size, AllocType, Desc, File, Line);
}


void MM_DELETE(void* ptr, const tChar* File, tU32 Line)
{
	delete ptr;
}


void MM_DELETE_A(void* ptr, const tChar* File, tU32 Line)
{
	delete[] ptr;
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
	MMDELETE(ptr);
}

void operator delete[](void* ptr)
{
	MMDELETEA(ptr); 
}


#endif // USE_MM_ALLOC
