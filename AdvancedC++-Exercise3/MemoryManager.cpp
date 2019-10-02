#include "MemoryManager.h"
#include "AllocDesc.h"
#include <stdio.h>
#include <string.h>


AllocDesc* MemoryManager::FreeList;

void* MemoryManager::MM_MALLOC(tU32 size, tU32 alloctype, const tChar* desc, const tChar* file, tU32 line)
{
	void* allocMem;

	AllocDesc* allocDesc = (AllocDesc*)malloc(sizeof(AllocDesc));

	if (MAX_OBJECT_SIZE >= size)
	{
		// use Small Object Allocator
		allocMem = SmallObjectAllocator::GetInstance()->Allocate(size);
		allocDesc->AllocationType = 0;
	}
	else
	{
		// use Simple Tracker Allocator
		allocMem = SimpleTrackerAllocator::GetInstance()->Allocate(size);
		allocDesc->AllocationType = 1;
	}

	allocDesc->Ptr = allocMem;
	allocDesc->Size = allocMem ? size : 0;
	allocDesc->Description = desc;
	allocDesc->File = file;
	allocDesc->Line = line;
	allocDesc->Freed = false;
	allocDesc->Next = nullptr;

	TraceAlloc(allocDesc);

	return allocMem;
};


void MemoryManager::MM_FREE(void* ptr, tU32 alloctype, const tChar* desc, const tChar* file, tU32 line)
{
	AllocDesc* allocDesc = GetDesc(ptr);
	size_t size = allocDesc->Size;

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

	TraceDealloc(allocDesc);
};


void* MemoryManager::MM_NEW(size_t size, tU32 alloctype, const tChar* desc, const tChar* file, tU32 line)
{
	return MM_MALLOC(size, alloctype, desc, file, line);
}


void* MemoryManager::MM_NEW_A(size_t size, tU32 alloctype, const tChar* desc, const tChar* file, tU32 line)
{
	return MM_MALLOC(size, alloctype, desc, file, line);
}


void MemoryManager::MM_DELETE(void* ptr, tU32 alloctype, const tChar* desc, const tChar* file, tU32 line)
{
	MM_FREE(ptr, 0, desc, file, line);
}


void MemoryManager::MM_DELETE_A(void* ptr, tU32 alloctype, const tChar* desc, const tChar* file, tU32 line)
{
	MM_FREE(ptr, 0, desc, file, line);
}


void MemoryManager::TraceAlloc(AllocDesc* desc)
{
	AllocDesc* p = FreeList;
	while (p != nullptr)
	{
		p = p->Next;
	}
	p = desc;
}


void MemoryManager::TraceDealloc(AllocDesc* desc)
{
	AllocDesc* p = FreeList;

	while (p->Ptr != desc->Ptr)
	{
		p = p->Next;
	}

	if (p) 
	{
		p->Freed = true;
	}
}


AllocDesc* MemoryManager::GetDesc(void* ptr)
{
	AllocDesc* p = FreeList;

	while (p->Ptr != ptr)
	{
		p = p->Next;
	}

	return p;
}


