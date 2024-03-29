#pragma once

#include <iostream>

// Defining types
typedef char tChar;
typedef uint32_t tU32;
typedef uint64_t tU64;

// Small Object Allocator configuration
const size_t CHUNK_SIZE = 64;
const size_t MIN_OBJECT_SIZE = 1;
const size_t MAX_OBJECT_SIZE = 8;

const unsigned char MinObjectsPerChunk_ = 8;
const unsigned char MaxObjectsPerChunk_ = UCHAR_MAX;

