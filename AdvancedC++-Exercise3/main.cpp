#include "MemoryManager.h"
#include <iostream>

int main()
{
	int* a = new int(555);
	delete a;
	return 0;
}