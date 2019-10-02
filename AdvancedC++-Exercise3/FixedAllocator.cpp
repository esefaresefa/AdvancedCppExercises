#include "FixedAllocator.h"
#include <cassert>


void* FixedAllocator::Allocate()
{
	if (_AllocChunk == 0 ||
		_AllocChunk->_BlocksAvailable == 0)
	{
		// No available memory in this chunk
		// Try to find one
		Chunks::iterator i = _Chunks.begin();
		for (;; ++i)
		{
			if (i == _Chunks.end())
			{
				// All filled up-add a new chunk
				_Chunks.reserve(_Chunks.size() + 1);
				Chunk newChunk;
				newChunk.Init(_BlockSize, _NumBlocks);
				_Chunks.push_back(newChunk);
				_AllocChunk = &_Chunks.back();
				_DeallocChunk = &_Chunks.back();
				break;
			}
			if (i->_BlocksAvailable > 0)
			{
				// Found a chunk
				_AllocChunk = &*i;
				break;
			}
		}
	}

	assert(_AllocChunk != 0);
	assert(_AllocChunk->_BlocksAvailable > 0);

	return _AllocChunk->Allocate(_BlockSize);
}


void FixedAllocator::Deallocate(void* BlockToDeallocate)
{
	if (_DeallocChunk != BlockToDeallocate)
	{
		const std::size_t chunkLength = _NumBlocks * _BlockSize;
		Chunk * LowerPtr = _DeallocChunk;
		Chunk * UpperPtr = _DeallocChunk + 1;
		const Chunk * loBound = &_Chunks.front();
		const Chunk * hiBound = &_Chunks.back() + 1;
		
		// Special case: deallocChunk_ is the last in the array
		if (UpperPtr == hiBound)
			UpperPtr = nullptr;
		
		while(true)
		{
			if (LowerPtr)
				{
					if (LowerPtr == BlockToDeallocate)
					{
						_DeallocChunk = LowerPtr;
						break;
					}
					if (LowerPtr->HasBlock(BlockToDeallocate, chunkLength))
						{
							LowerPtr = nullptr;
							if (UpperPtr == nullptr) break;
						}
					else --LowerPtr;
				}
			
				if (UpperPtr)
				{
					if (UpperPtr->HasBlock(BlockToDeallocate, chunkLength))
					{
						_DeallocChunk = UpperPtr;
						break;
					}
					if (++UpperPtr == hiBound)
						{
							UpperPtr = nullptr;
							if (LowerPtr == nullptr) break;
						}
				}
		}
			
		// if no ptr found, exception?
		if (!UpperPtr && !LowerPtr)
			return;


	}
		
	_DeallocChunk->Deallocate(BlockToDeallocate, _BlockSize);
}


