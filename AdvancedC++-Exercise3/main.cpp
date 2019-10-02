#include "MemoryManager.h"
#include <iostream>


class A
{
	int a;
	int b;
	int c;
};


int main()
{
	A* a = new A();
	A* b = new A();
	delete b;
	delete a;

	MemoryManager::DumpMemory();

	return 0;
}