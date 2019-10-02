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

	const Chunk* HasBlock(void* p);

	bool TrimEmptyChunk(void);

	bool TrimChunkList(void);

private:

	size_t _BlockSize;

	unsigned char _NumBlocks;

	typedef std::vector<Chunk> Chunks;

	Chunks _Chunks;

	Chunk* _AllocChunk;

	Chunk* _DeallocChunk;

	Chunk* _EmptyChunk;

	static unsigned char MinObjectsPerChunk_;
		
	static unsigned char MaxObjectsPerChunk_;
};

unsigned char FixedAllocator::MinObjectsPerChunk_ = 8;
unsigned char FixedAllocator::MaxObjectsPerChunk_ = UCHAR_MAX;