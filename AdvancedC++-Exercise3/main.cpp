#include "MemoryManager.h"
#include <iostream>


class Test
{
	int a, b, c;
};


int main()
{
	Test* a = new Test();
	Test* b = new Test();
	Test* c = new Test();
	delete b;
	delete a;
	// c leaked!

	int* aa = new int[5];
	Test* bb = new Test[5];
	int* cc = new int[5];
	delete[] aa;
	delete[] bb;
	// cc leaked!

	/*
	int* aaa = new int(555);
	int* bbb = new int(666);
	int* ccc = new int(777);
	delete aaa;
	// bbb leaked!
	// delete bbb;
	delete ccc;
	*/

	MemoryManager::DumpMemory();

	delete[] cc;
	delete c;
	return 0;
}