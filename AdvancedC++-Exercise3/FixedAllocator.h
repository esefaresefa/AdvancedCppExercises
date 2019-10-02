#pragma once

#include "Chunk.h"
#include<vector>

class FixedAllocator
{
public:

	FixedAllocator();

	FixedAllocator(const FixedAllocator& other);

	FixedAllocator& operator=(const FixedAllocator&);

	~FixedAllocator();

	void Initialize(size_t blockSize, size_t pageSize);

	void* Allocate();

	bool Deallocate(void* ChunkToDeallocate);

private:

	size_t _BlockSize;

	unsigned char _NumBlocks;

	typedef std::vector<Chunk, std::allocator<Chunk>> Chunks;

	Chunks _Chunks;

	Chunk* _AllocChunk;

	Chunk* _DeallocChunk;

	Chunk* _EmptyChunk;
};