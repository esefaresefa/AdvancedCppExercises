#include "MemoryManager.h"
#include "AllocDesc.h"
#include <stdio.h>
#include <string.h>
#include <iostream>


AllocDesc* MemoryManager::FreeList;

void* MemoryManager::MM_MALLOC(tU32 size, tU32 alloctype, const tChar* desc, const tChar* file, tU32 line)
{
	void* allocMem;

	AllocDesc* allocDesc = (AllocDesc*)malloc(sizeof(AllocDesc));

	if (MAX_OBJECT_SIZE >= size && MIN_OBJECT_SIZE <= size)
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
	allocDesc->Freed = !allocMem;
	allocDesc->Next = nullptr;

	TraceAlloc(allocDesc);

	return allocMem;
};


void MemoryManager::MM_FREE(void* ptr, tU32 alloctype, const tChar* desc, const tChar* file, tU32 line)
{
	AllocDesc* allocDesc = GetDesc(ptr);
	if(allocDesc && !allocDesc->Freed)
	{
		tU32 allocType = allocDesc->AllocationType;
		size_t size = allocDesc->Size;

		if (allocType == 0)
		{
			// use Small Object Allocator
			SmallObjectAllocator::GetInstance()->Deallocate(ptr, size);
		}
		else if(allocType == 1)
		{
			// use Simple Tracker Allocator
			SimpleTrackerAllocator::GetInstance()->Deallocate(ptr);
		}

		TraceDealloc(allocDesc);
	}
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


void MemoryManager::PrintMemory()
{
	AllocDesc* p = FreeList;

	while (p != nullptr)
	{
		std::cout	
				<< "Memory address: " << p->Ptr
				<< ", Freed: " << (p->Freed == false ? "false" : "true")
				<< ", Allocation type: " << p->AllocationType
				<< ", Allocation size: " << p->Size
				// << ", File: " << p->File
				// << ", Line: " << p->Line
				<< std::endl;

		p = p->Next;
	}
}


void MemoryManager::TraceAlloc(AllocDesc* desc)
{
	if (!FreeList)
	{
		FreeList = desc;
	}
	else 
	{
		AllocDesc* p = FreeList;
		while (p->Next != nullptr)
		{
			p = p->Next;
		}
		p->Next = desc;
	}
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

	while (p)
	{
		if (p->Ptr == ptr)
			break;
		p = p->Next;
	}

	return p;
}
