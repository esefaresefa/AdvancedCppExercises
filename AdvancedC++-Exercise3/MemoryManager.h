#pragma once

#include "MMConfig.h"
#include "AllocDesc.h"
#include "SmallObject.h"
#include "SimpleTracker.h"
#include <map>



class MemoryManager
{
public:

	static void* MM_MALLOC(tU32 size, tU32 alloctype, const tChar* desc, const tChar* file, tU32 line);

	static void MM_FREE(void* ptr, tU32 alloctype, const tChar* desc, const tChar* file, tU32 line);

	static void* MM_NEW(size_t size, tU32 alloctype, const tChar* desc, const tChar* file, tU32 line);

	static void* MM_NEW_A(size_t size, tU32 alloctype, const tChar* desc, const tChar* file, tU32 line);

	static void MM_DELETE(void* ptr, tU32 alloctype, const tChar* desc, const tChar* file, tU32 line);

	static void MM_DELETE_A(void* ptr, tU32 alloctype, const tChar* desc, const tChar* file, tU32 line);

	static void DumpMemory();

protected:

	static void TraceAlloc(AllocDesc* desc);

	static void TraceDealloc(AllocDesc* desc);

	static AllocDesc* GetDesc(void* ptr);

private:

	static AllocDesc* FreeList;
};


/* ////////////////////////// ALLOCATOR ////////////////////////// */
template<typename T>
class MMAllocator
{
public:

	MMAllocator() {};

	T* allocate(size_t cnt)
	{
		return reinterpret_cast<T*>(_MMObject.allocate(sizeof(T) * cnt));
	}

	void deallocate(T* p, size_t cnt)
	{
		_MMObject.deallocate(p, sizeof(T) * cnt);
	}

	void construct(T* p, T const& val)
	{
		::new((void *)p) T(val);
	}

	void destroy(T* p)
	{
		return ((T*)p)->~T();
	}

	using value_type = T;

private:
	static MemoryManager _MMObject;
};


template<typename T>
MemoryManager MMAllocator<T>::_MMObject;
