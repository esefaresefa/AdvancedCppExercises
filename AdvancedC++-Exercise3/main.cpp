#include "Config.h"

#include <iostream>


// Defining types
typedef char tChar;
typedef uint32_t tU32;


// Defining function helpers
#define Malloc(SIZE, TYPE, DESC) _Malloc(SIZE, TYPE, DESC, __FILE__, __LINE__)
#define Realloc(PTR, SIZE) _Realloc(PTR, SIZE, __FILE__, __LINE__)
#define New(CLASS, TYPE, DESC) new(TYPE, DESC, __FILE__, __LINE__) CLASS
#define Delete delete


// Heap Store, overloading operators
void* _Malloc(tU32 Size, tU32 AllocType, const tChar* Desc, const tChar* File, tU32 Line) 
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

void* _Realloc(void* Ptr, tU32 Size, const tChar* File, tU32 Line) 
{ 
	return nullptr; 
};

void _Free(void* Ptr) 
{};


// Free Store, overloading operators new and delete
void* operator new(size_t size) 
{ 
	// MemoryManager::Trace(size); // TODO trace   
	return nullptr; 
}

void* operator new[](size_t size) 
{
	// MemoryManager::AllocTrace(size); // TODO trace   
	return nullptr; 
}

inline void* operator new(size_t Size, tU32 AllocType, const tChar* Desc, const tChar* File, tU32 Line) 
{	
	// MemoryManager::AllocTrace(Size, AllocType, Desc, File, Line); // TODO trace
	return _Malloc(Size, AllocType, Desc, File, Line); 
}

inline void* operator new[](size_t Size, tU32 AllocType, const tChar* Desc, const tChar* File, tU32 Line) 
{ 
	// MemoryManager::AllocTrace(Size, AllocType, Desc, File, Line); // TODO trace
	return _Malloc(Size, AllocType, Desc, File, Line); 
}

inline void operator delete(void* Ptr) 
{
	// MemoryManager::FreeTrace(Ptr); // TODO trace
	_Free(Ptr); 
}

inline void operator delete[](void* Ptr) 
{ 
	// MemoryManager::FreeTrace(Ptr); // TODO trace
	_Free(Ptr); 
}


int main()
{
	int* a = new int{555};
	return 0;
}