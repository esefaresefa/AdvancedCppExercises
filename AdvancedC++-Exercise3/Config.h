#pragma once

// Using custom memory manager MM
#define USE_MM_ALLOC

// Small Object Allocator configuration
const size_t CHUNK_SIZE = 64;
const size_t MAX_OBJECT_SIZE = 8;

