#pragma once

#include "MMConfig.h"

struct AllocDesc
{
	// Allocation address
	void* Ptr;

	// Allocation size
	tU32 Size;

	// Allocation category
	tU32 AllocationType;

	// Descripiton string
	std::string Description;

	// Next allocation
	AllocDesc* Next;
};