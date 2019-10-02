#include "Chunk.h"
#include <cassert>


void Chunk::Init(size_t blockSize, unsigned char blocks)
{
	_Data = new unsigned char[blockSize * blocks];
	_FirstAvailableBlock = 0;
	_BlocksAvailable = blocks;
	
	unsigned char i = 0;
	unsigned char* p = _Data;
	for (; i != blocks; p += blockSize)
	{
		*p = ++i;
	}
}


void* Chunk::Allocate(size_t blockSize)
{
	if (!_BlocksAvailable)
		return 0;

	unsigned char* pResult = _Data + (_FirstAvailableBlock * blockSize);

	// _FirstAvailableBlock points to the next available block
	_FirstAvailableBlock = *pResult;
	--_BlocksAvailable;

	return pResult;
}


void Chunk::Deallocate(void* p, size_t blockSize)
{
	// Position check
	assert(p >= _Data);

	unsigned char* toRelease = static_cast<unsigned char*>(p);

	// Alignment check
	assert((toRelease - _Data) % blockSize == 0);

	*toRelease = _FirstAvailableBlock;
	_FirstAvailableBlock = static_cast<unsigned char>((toRelease - _Data) / blockSize);
	
	// Truncation check
	assert(_FirstAvailableBlock == (toRelease - _Data) / blockSize);

	++_BlocksAvailable;
}

void Chunk::Release()
{
	assert(_Data != nullptr);

	::operator delete (_Data);
}
