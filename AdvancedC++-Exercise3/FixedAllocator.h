#pragma once

#include "Chunk.h"
#include<vector>

class FixedAllocator
{
public:

	void* Allocate();

private:

	size_t _BlockSize;

	unsigned char _NumBlocks;

	typedef std::vector<Chunk> Chunks;

	Chunks _Chunks;

	Chunk* _AllocChunk;

	Chunk* _DeallocChunk;
};