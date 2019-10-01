#pragma once

#include "Singleton.h"
#include "SmallObjAllocator.h"



class SmallObject
{
public:

	static void* operator new(size_t size);

	static void operator delete(void* p, size_t size);

	virtual ~SmallObject() {}
};



typedef Singleton<SmallObjAllocator> SOAllocator;

void* SmallObject::operator new(std::size_t size)
{
	return SOAllocator::GetInstance()->Allocate(size);
}

void SmallObject::operator delete(void* p, std::size_t size)
{
	SOAllocator::GetInstance()->Deallocate(p, size);
}