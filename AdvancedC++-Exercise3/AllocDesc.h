#pragma once

#include "MMConfig.h"

struct AllocDesc
{
public:
	// Allocation address
	void* Ptr;

	// Allocation size
	tU32 Size;

	// Allocation category
	tU32 AllocationType;

	// Descripiton string
	const tChar* Description;

	// File of the allocation
	const tChar* File;

	// Code line of the allocation
	tU32 Line;

	// Allocation Freed
	bool Freed;

	// Next allocation
	AllocDesc* Next;
};