#include "SmallObject.h"


void* SmallObject::operator new(std::size_t size)
{
	return SmallObjectAllocator::GetInstance()->Allocate(size);
}

void SmallObject::operator delete(void* p, std::size_t size)
{
	SmallObjectAllocator::GetInstance()->Deallocate(p, size);
}