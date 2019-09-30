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
		alist.push_back(444);
		alist.push_back(555);
		alist.push_back(666);

		SListArray<int>::iterator abiterator = alist.begin();
		assert(*abiterator++ == 444);
		assert(*abiterator++ == 555);
		assert(*abiterator++ == 666);

		std::cout << "OK!" << std::endl;

		// FixedSList
		std::cout << "FixedSList::iterator operator++ test... ";

		FixedSList<int, 5> flist;
		flist.push_back(777);
		flist.push_back(888);
		flist.push_back(999);

		FixedSList<int, 5>::iterator fiterator = flist.begin();
		assert(*fiterator++ == 777);
		assert(*fiterator++ == 888);
		assert(*fiterator++ == 999);

		std::cout << "OK!" << std::endl;
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