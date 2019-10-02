#include "SmallObjAllocator.h"

// SmallObjAllocator::SmallObjAllocator ---------------------------------------

 SmallObjAllocator::SmallObjAllocator(size_t pageSize, size_t maxObjectSize) :
_MaxSmallObjectSize(maxObjectSize)
 {
	     for (size_t i = 0; i < maxObjectSize; ++i)
			 _Pool[i].Initialize(i+1, pageSize);
 }

 // SmallObjAllocator::~SmallObjAllocator --------------------------------------

 SmallObjAllocator::~SmallObjAllocator()
 {
		     // _Pool.clear();
 }

 // SmallObjAllocator::Allocate ------------------------------------------------

 void * SmallObjAllocator::Allocate(size_t numBytes)
 {
	 FixedAllocator& alloc = _Pool[numBytes - 1];
	 return alloc.Allocate();
 }

 // SmallObjAllocator::Deallocate ----------------------------------------------

 void SmallObjAllocator::Deallocate(void * p, size_t numBytes)
 {
	 FixedAllocator& alloc = _Pool[numBytes - 1];
	 alloc.Deallocate(p);
 }