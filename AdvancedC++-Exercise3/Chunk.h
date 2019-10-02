#pragma once


struct Chunk
{
	void Init(size_t blockSize, unsigned char blocks);

	void* Allocate(size_t blockSize);

	void Deallocate(void* p, size_t blockSize);

	unsigned char* _Data;

	unsigned char _FirstAvailableBlock;

	unsigned char _BlocksAvailable;

	inline bool HasBlock(void* p, std::size_t chunkLength) const
	{
		unsigned char * pc = static_cast<unsigned char *>(p);
		return (_Data <= pc) && (pc < _Data + chunkLength);
	}
};
