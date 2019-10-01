#include "Config.h"
#include <iostream>

#ifdef USE_MM_ALLOC

// Defining types
typedef char tChar;
typedef uint32_t tU32;

// Defining function helpers
#define Malloc(SIZE, TYPE, DESC) _Malloc(SIZE, TYPE, DESC, __FILE__, __LINE__)
#define Realloc(PTR, SIZE) _Realloc(PTR, SIZE, __FILE__, __LINE__)
#define New(CLASS, TYPE, DESC) new(TYPE, DESC, __FILE__, __LINE__) CLASS
#define Delete delete

void* operator new(size_t size)
{
	// MM_NEW(); // TODO
	return nullptr; 
}

void* operator new[](size_t size)
{
	// MM_NEW_ARRAY(); // TODO
	return nullptr;
}

void operator delete(void* Ptr)
{
	// MM_DELETE(Ptr); // TODO
}

void operator delete[](void* Ptr)
{
	// MM_DELETE_ARRAY(Ptr); // TODO
}


// Heap Store, overloading operators
void* MM_ALLOC(tU32 Size, tU32 AllocType, const tChar* Desc, const tChar* File, tU32 Line)
{
	void* allocMem;

	if (MAX_OBJECT_SIZE >= Size)
	{
		allocMem = nullptr;// TODO SmallObjAllocator
	}
	else
	{
		allocMem = nullptr;// TODO normal new
	}

	// MemoryManager::Trace(Size, AllocType, Desc, File, Line); // TODO trace

	return allocMem;
};

void* MM_REALLOC(void* Ptr, tU32 Size, const tChar* File, tU32 Line)
{
	// TODO
	return nullptr;
};

void MM_FREE(void* Ptr)
{};

#endif // USE_MM_ALLOC



int main()
{
	int* a = new int{555};
	return 0;
}