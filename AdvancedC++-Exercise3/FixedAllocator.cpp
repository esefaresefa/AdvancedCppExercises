#include "FixedAllocator.h"
#include <cassert>
#include "MMConfig.h"



FixedAllocator::FixedAllocator()
	: _BlockSize(0)
	, _NumBlocks(0)
	, _Chunks()
	, _AllocChunk(NULL)
	, _DeallocChunk(NULL)
	, _EmptyChunk(NULL)
{
}


FixedAllocator::FixedAllocator(const FixedAllocator& other)
{
	_BlockSize = other._BlockSize;
	_NumBlocks = other._NumBlocks;
	_Chunks = other._Chunks;
	_AllocChunk = other._AllocChunk;
	_DeallocChunk = other._DeallocChunk;
	_EmptyChunk = other._EmptyChunk;
}


FixedAllocator& FixedAllocator::operator=(const FixedAllocator &other)
{
	FixedAllocator aux(other);
	std::swap(*this, aux);
	return *this;
}


FixedAllocator::~FixedAllocator()
{
	for (Chunks::iterator i(_Chunks.begin()); i != _Chunks.end(); ++i)
		i->Release();
}


void FixedAllocator::Initialize(size_t blockSize, size_t pageSize)
{
	assert(blockSize > 0);
	assert(pageSize >= blockSize);

	_BlockSize = blockSize;
	
	size_t numBlocks = pageSize / blockSize;

	if (numBlocks > MaxObjectsPerChunk_)
		numBlocks = MaxObjectsPerChunk_;
	else if (numBlocks < MinObjectsPerChunk_)
		numBlocks = MinObjectsPerChunk_;
	
	_NumBlocks = static_cast<unsigned char>(numBlocks);
}


void* FixedAllocator::Allocate()
{
	if (_AllocChunk == 0 ||
		_AllocChunk->_BlocksAvailable == 0)
	{
		if (_EmptyChunk != nullptr)
		{
			_AllocChunk = _EmptyChunk;
			_EmptyChunk = nullptr;
		}
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
	else if (_AllocChunk == _EmptyChunk)
		// detach _EmptyChunk from _AllocChunk, because after calling _AllocChunk->Allocate(_BlockSize); the chunk is no longer empty.
		_EmptyChunk = nullptr;

	assert(_AllocChunk != 0);
	assert(_AllocChunk->_BlocksAvailable > 0);

	return _AllocChunk->Allocate(_BlockSize);
}


bool FixedAllocator::Deallocate(void* BlockToDeallocate)
{
	// if block is not inside the last chunk deallocated
	const std::size_t chunkLength = _NumBlocks * _BlockSize;

	if (_DeallocChunk->HasBlock(BlockToDeallocate, chunkLength))
	{
		Chunk * LowerPtr = _DeallocChunk;
		Chunk * UpperPtr = _DeallocChunk + 1;
		const Chunk * loBound = &_Chunks.front();
		const Chunk * hiBound = &_Chunks.back() + 1;

		// Special case: deallocChunk_ is the last in the array
		if (UpperPtr == hiBound)
			UpperPtr = nullptr;

		while (true)
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


		// if no ptr found, return false to SmallObjAllocator that calls the default deallocator
		if (!UpperPtr && !LowerPtr)
			return false;
	}

	// if ptr found
	_DeallocChunk->Deallocate(BlockToDeallocate, _BlockSize);

	if (_DeallocChunk->HasAvailable(_NumBlocks))
	{
		assert(_EmptyChunk != _DeallocChunk);

		// Chunk is released only if there are 2 empty chunks.
		if (NULL != _EmptyChunk)
		{
			// If last Chunk is empty, just change what _DeallocChunk
				// points to, and release the last.  Otherwise, swap an empty
				// Chunk with the last, and then release it.
			Chunk* lastChunk = &_Chunks.back();

			if (lastChunk == _DeallocChunk)
				_DeallocChunk = _EmptyChunk;
			else if (lastChunk != _EmptyChunk)
					std::swap(*_EmptyChunk, *lastChunk);

			assert(lastChunk->HasAvailable(_NumBlocks));

			lastChunk->Release();

			_Chunks.pop_back();
			if ((_AllocChunk == lastChunk) || _AllocChunk->_BlocksAvailable == 0)
				_AllocChunk = _DeallocChunk;
		}
		_EmptyChunk = _DeallocChunk;
	}
		
	return true;
}


