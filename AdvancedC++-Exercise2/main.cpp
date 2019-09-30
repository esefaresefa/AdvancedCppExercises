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

	SList<int>list2(12);
	assert(list2.size()==12);

	SList<int>list3(12,5);
	assert(list3.size() == 12);
	for (SList<int>::iterator i = list3.begin(); i != list3.end(); ++i)
	{
		assert(*biterator == 5);
	}

	std::cout << std::endl;

	return 0;
}