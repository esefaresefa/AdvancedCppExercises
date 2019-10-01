#pragma once

#include "Singleton.h"
#include "SmallObjAllocator.h"



class SmallObject
{
public:

	void* operator new(size_t size);

	void operator delete(void* p, size_t size);

	virtual ~SmallObject() {}
};


typedef Singleton<SmallObjAllocator> SmallObjectAllocator;
