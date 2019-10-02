#include "SmallObjAllocator.h"
#include <cassert>

inline std::size_t GetOffset(std::size_t numBytes, std::size_t alignment)
{
	     const std::size_t alignExtra = alignment - 1;
	     return (numBytes + alignExtra) / alignment;
}


// SmallObjAllocator::SmallObjAllocator ---------------------------------------

 SmallObjAllocator::SmallObjAllocator(std::size_t pageSize, std::size_t maxObjectSize, std::size_t objectAlignSize) :
_Pool(NULL),
_MaxSmallObjectSize(maxObjectSize),
_ObjectAlignSize(objectAlignSize)
{
		 assert(0 != objectAlignSize);
	     const std::size_t allocCount = GetOffset(maxObjectSize, objectAlignSize);
		 _Pool = new FixedAllocator[allocCount];
	     for (std::size_t i = 0; i < allocCount; ++i)
			 _Pool[i].Initialize((i + 1) * objectAlignSize, pageSize);
}

 // SmallObjAllocator::~SmallObjAllocator --------------------------------------

 SmallObjAllocator::~SmallObjAllocator(void)
{
		     delete[] _Pool;
}

 // SmallObjAllocator::TrimExcessMemory ----------------------------------------

 bool SmallObjAllocator::TrimExcessMemory(void)
 {
	     bool found = false;
	     const std::size_t allocCount = GetOffset(_MaxSmallObjectSize, _ObjectAlignSize);
	     std::size_t i = 0;
	     for (; i < allocCount; ++i)
		     {
		         if (_Pool[i].TrimEmptyChunk())
			             found = true;
		     }
	     for (i = 0; i < allocCount; ++i)
		     {
		         if (_Pool[i].TrimChunkList())
			             found = true;
		     }
	
		     return found;
	 }

 // SmallObjAllocator::Allocate ------------------------------------------------

 void * SmallObjAllocator::Allocate(std::size_t numBytes)
 {	
		     //assert(NULL != _Pool);
	     if (0 == numBytes) numBytes = 1;
	     const std::size_t index = GetOffset(numBytes, _ObjectAlignSize) - 1;
	     const std::size_t allocCount = GetOffset(_MaxSmallObjectSize, _ObjectAlignSize);
	     (void)allocCount;
	     assert(index < allocCount);
	
		     FixedAllocator & allocator = _Pool[index];
	     //assert(allocator.BlockSize() >= numBytes);
	     //assert(allocator.BlockSize() < numBytes + GetAlignment());
	     void * place = allocator.Allocate();
	
		     if ((NULL == place) && TrimExcessMemory())
		         place = allocator.Allocate();

	     return place;
	 }

 // SmallObjAllocator::Deallocate ----------------------------------------------

 void SmallObjAllocator::Deallocate(void * p, std::size_t numBytes)
 {
	     if (NULL == p) return;
	     //assert(NULL != _Pool);
	     if (0 == numBytes) numBytes = 1;
	     const std::size_t index = GetOffset(numBytes, _ObjectAlignSize) - 1;
	     const std::size_t allocCount = GetOffset(_MaxSmallObjectSize, _ObjectAlignSize);
	     (void)allocCount;
	     assert(index < allocCount);
	     FixedAllocator & allocator = _Pool[index];
	     //assert(allocator.BlockSize() >= numBytes);
	     //assert(allocator.BlockSize() < numBytes + GetAlignment());
	     const bool found = allocator.Deallocate(p, NULL);
	     (void)found;
	     assert(found);
	 }

 // SmallObjAllocator::Deallocate ----------------------------------------------

 void SmallObjAllocator::Deallocate(void * p)
 {
	     if (NULL == p) return;
	     //assert(NULL != _Pool);
	     FixedAllocator * pAllocator = NULL;
	     const std::size_t allocCount = GetOffset(_MaxSmallObjectSize, _ObjectAlignSize);
	     Chunk * chunk = NULL;
	
		     for (std::size_t ii = 0; ii < allocCount; ++ii)
		     {
		         chunk = _Pool[ii].HasBlock(p);
		         if (NULL != chunk)
			         {
			             pAllocator = &_Pool[ii];
			             break;
			         }
		     }
	
		     assert(NULL != chunk);
	     const bool found = pAllocator->Deallocate(p, chunk);
	     (void)found;
	     assert(found);
	 }