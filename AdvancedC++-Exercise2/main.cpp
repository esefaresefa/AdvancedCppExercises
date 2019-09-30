#include "SList.h"
#include "SListArray.h"
#include "FixedSList.h"
#include <iostream>
#include <cassert>

using namespace list;

int main()
{
	// TESTING ITERATORS
	{
		// SList
		std::cout << "SList::iterator operator++ test... ";

		SList<int> slist;
		slist.push_back(111);
		slist.push_back(222);
		slist.push_back(333);

		SList<int>::iterator siterator = slist.begin();
		assert(*siterator++ == 111);
		assert(*siterator++ == 222);
		assert(*siterator++ == 333);

		std::cout << "OK!" << std::endl;

		// SListArray
		std::cout << "SListArray::iterator operator++ test... ";

		SListArray<int> alist;
		alist.push_back(111);
		alist.push_back(222);
		alist.push_back(333);

		SListArray<int>::iterator abiterator = alist.begin();
		assert(*abiterator++ == 111);
		assert(*abiterator++ == 222);
		assert(*abiterator++ == 333);

		std::cout << "OK!" << std::endl;

		// FixedSList
		/*
		std::cout << "FixedSList::iterator operator++ test... ";

		FixedSList<int> alist;
		alist.push_back(111);
		alist.push_back(222);
		alist.push_back(333);

		FixedSList<int>::iterator biterator = alist.begin();
		assert(*biterator++ == 111);
		assert(*biterator++ == 222);
		assert(*biterator++ == 333);

		std::cout << "OK!" << std::endl;
		*/
	}


	SList<int>list2(12);
	assert(list2.size()==12);

	SList<int>list3(12,5);
	assert(list3.size() == 12);
	for (SList<int>::iterator i = list3.begin(); i != list3.end(); ++i)
	{
		assert(*i == 5);
	}

	std::cout << std::endl;

	return 0;
}