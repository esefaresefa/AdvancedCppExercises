#include "MemoryManager.h"
#include <iostream>


class Test
{
public:
	Test() { a = 555; b = 666; c = 777; }
	void print() { std::cout << a << ", " << b << ", " << c << std::endl; }
private:
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
	delete ccc;
	*/

	MemoryManager::DumpMemory();

	// delete bbb;
	delete[] cc;
	delete c;
	return 0;
}