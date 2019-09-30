#include "SList.h"
#include <iostream>
#include <cassert>

using namespace slist;
int main()
{
	SList<int> list;
	list.push_back(111);
	list.push_back(222);
	list.push_back(333);

	std::cout << "Iterator operator++ test... ";
	SList<int>::iterator biterator = list.begin();
	assert(*biterator++ == 111);
	assert(*biterator++ == 222);
	assert(*biterator++ == 333);
	std::cout << "OK!" << std::endl;

	std::cout << std::endl;

	return 0;
}