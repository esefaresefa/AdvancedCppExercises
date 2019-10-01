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


