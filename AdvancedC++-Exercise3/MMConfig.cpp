#include "MemoryManager.h"
// #include <cstdio>
// #include <cstdlib>
#include <new>

#ifdef  USE_MM_ALLOC

// Defining function helpers
#define MMNEW(size, type, desc)			MemoryManager::MM_NEW(size, type, desc, __FILE__, __LINE__)
#define MMNEWA(size, type, desc)		MemoryManager::MM_NEW_A(size, type, desc, __FILE__, __LINE__)
#define MMDELETE(ptr, type, desc)		MemoryManager::MM_DELETE(ptr, type, desc, __FILE__, __LINE__)
#define MMDELETEA(ptr, type, desc)		MemoryManager::MM_DELETE_A(ptr, type, desc, __FILE__, __LINE__)
#define MMALLOC(ptr, size, type, desc)	MemoryManager::MM_MALLOC(ptr, size, type, desc, __FILE__, __LINE__)
#define MMFREE(ptr, type, desc)			MemoryManager::MM_FREE(ptr, type, desc, __FILE__, __LINE__)

void* operator new(size_t size) noexcept
{
	return MMNEW(size, 0, "");
}

void* operator new[](size_t size) noexcept
{
	return MMNEWA(size, 0, "");
}

void operator delete(void* ptr) noexcept
{
	MMDELETE(ptr, 0, "");
}

void operator delete[](void* ptr) noexcept
{
	MMDELETEA(ptr, 0, "");
}

#endif // USE_MM_ALLOC