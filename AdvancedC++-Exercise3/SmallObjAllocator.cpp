#include "SmallObjAllocator.h"

// SmallObjAllocator::SmallObjAllocator ---------------------------------------

 SmallObjAllocator::SmallObjAllocator(std::size_t pageSize, std::size_t maxObjectSize) :
_Pool(maxObjectSize),
_MaxSmallObjectSize(maxObjectSize)
 {
	     for (std::size_t i = 0; i < maxObjectSize; ++i)
			 _Pool[i].Initialize(i+1, pageSize);
 }

 // SmallObjAllocator::~SmallObjAllocator --------------------------------------

 SmallObjAllocator::~SmallObjAllocator()
 {
		     _Pool.clear();
 }

 // SmallObjAllocator::Allocate ------------------------------------------------

 void * SmallObjAllocator::Allocate(std::size_t numBytes)
 {
	 FixedAllocator& alloc = _Pool[numBytes - 1];
	 return alloc.Allocate();
 }

 // SmallObjAllocator::Deallocate ----------------------------------------------

 void SmallObjAllocator::Deallocate(void * p, std::size_t numBytes)
 {
	 FixedAllocator& alloc = _Pool[numBytes - 1];
	 alloc.Deallocate(p);
 }