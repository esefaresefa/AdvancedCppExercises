#include "SList.h"
#include "SListArray.h"
#include "FixedSList.h"
#include <iostream>
#include <cassert>

using namespace list;

int main()
{
	// TESTING SList CONSTRUCTORS
	{



		std::cout << std::endl << "SList constructors ////////////////////////////////////////////////////////////////////////////////////" << std::endl;
		// SList
		std::cout << "SList default constructor... ";
		SList<int> slist;
		std::cout << "OK!" << std::endl;

		// FixedSList
		std::cout << "FixedSList default constructor... ";
		FixedSList<int, 1> flist;
		std::cout << "OK!" << std::endl;

		std::cout << "fill constructor... ";
		SList<int>list2(12);
		assert(list2.size() == 12);

		std::cout << std::endl << "fill constructor with val ...";
		SList<int>list3(12, 5);
		assert(list3.size() == 12);
		for (SList<int>::iterator i = list3.begin(); i != list3.end(); ++i)
		{
			assert(*i == 5);
		}


		std::cout << std::endl << "iterator constructor ...";
		SList<int>list4(++list3.begin(), list3.end());
		assert(list4.size() == 11);
		for (SList<int>::iterator i = list4.begin(); i != list4.end(); ++i)
		{
			assert(*i == 5);
		}


		std::cout << std::endl << "copy constructor ...";
		SList<int>list5(list4);
		assert(list5.size() == 11);
		for (SList<int>::iterator i = list5.begin(); i != list5.end(); ++i)
		{
			assert(*i == 5);
		}

		std::cout << std::endl << "move constructor ...";
		SList<int>list6(std::move(list4));
		assert(list6.size() == 11);
		for (SList<int>::iterator i = list6.begin(); i != list6.end(); ++i)
		{
			assert(*i == 5);
		}
		assert(list4.size() == 0);

		std::cout << std::endl << "inizializer list constructor ...";
		SList<int>list7{ 0,1,2,3,4 };
		assert(list7.size() == 5);
		int val = 0;
		for (SList<int>::iterator i = list7.begin(); i != list7.end(); ++i, ++val)
		{
			assert(*i == val);
		}

		std::cout << std::endl << "destructor ...";
		list7.~SList<int>();
		std::cout << std::endl << "size ...";
		assert(list7.size() == 0);
		std::cout << std::endl << "empty on empty ...";
		assert(list7.empty());

	}


	// TESTING SArrayList CONSTRUCTORS
	{
		std::cout << std::endl << std::endl << "SArrayList constructors //////////////////////////////////////////////////////////////////////////////////// " << std::endl;
		// SListArray
		std::cout << "SListArray default constructor... ";
		SListArray<int> alist;
		std::cout << "OK!" << std::endl;

		// SListArray range constructor
		std::cout << "range constructor... ";
		alist.push_back(1);
		alist.push_back(2);
		alist.push_back(3);
		SListArray<int> alist2(alist.begin(), alist.end());
		SListArray<int>::const_iterator aiterator = alist2.cbegin();
		assert(*aiterator++ == 1);
		assert(*aiterator++ == 2);
		assert(*aiterator++ == 3);
		std::cout << "OK!" << std::endl;

		std::cout << std::endl  << "fill constructor... ";
		SListArray<int>list2(12);
		assert(list2.size() == 12);

		std::cout << std::endl << "fill constructor with val ...";
		SListArray<int>list3(12, 5);
		assert(list3.size() == 12);
		for (SListArray<int>::iterator i = list3.begin(); i != list3.end(); ++i)
		{
			assert(*i == 5);
		}


		std::cout << std::endl << "iterator constructor ...";
		SListArray<int>list4(++list3.begin(), list3.end());
		assert(list4.size() == 11);
		for (SListArray<int>::iterator i = list4.begin(); i != list4.end(); ++i)
		{
			assert(*i == 5);
		}


		std::cout << std::endl << "copy constructor ...";
		SListArray<int>list5(list4);
		assert(list5.size() == 11);
		for (SListArray<int>::iterator i = list5.begin(); i != list5.end(); ++i)
		{
			assert(*i == 5);
		}

		std::cout << std::endl << "move constructor ...";
		SListArray<int>list6(std::move(list4));
		assert(list6.size() == 11);
		for (SListArray<int>::iterator i = list6.begin(); i != list6.end(); ++i)
		{
			assert(*i == 5);
		}
		assert(list4.size() == 0);

		std::cout << std::endl << "inizializer list constructor ...";
		SListArray<int>list7{ 0,1,2,3,4 };
		assert(list7.size() == 5);
		int val = 0;
		for (SListArray<int>::iterator i = list7.begin(); i != list7.end(); ++i, ++val)
		{
			assert(*i == val);
		}

		std::cout << std::endl << "destructor ...";
		list7.~SListArray<int>();
		std::cout << std::endl << "size ...";
		assert(list7.size() == 0);
		std::cout << std::endl << "empty on empty ...";
		assert(list7.empty());

	}


	// TESTING ITERATORS
	{

		std::cout << std::endl << std::endl << " ITERATORS //////////////////////////////////////////////////////////////////////////////////// " << std::endl;
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

	// TESTING SLIST modifiers
	{


		std::cout << std::endl << std::endl << "SList modifiers //////////////////////////////////////////////////////////////////////////////////// " << std::endl;

		SList<int>list6(11, 5);

		std::cout << std::endl << "operator= ...";
		SList<int>list8 = list6;
		assert(list8.size() == 11);
		for (SList<int>::iterator i = list8.begin(); i != list8.end(); ++i)
		{
			assert(*i == 5);
		}

		std::cout << std::endl << "operator= move ...";
		SList<int>list9 = std::move(list6);
		assert(list9.size() == 11);
		for (SList<int>::iterator i = list9.begin(); i != list9.end(); ++i)
		{
			assert(*i == 5);
		}
		assert(list6.size() == 0);


		std::cout << std::endl << "operator= inizializer list ...";
		SList<int>list10 = { 0,1,2,3,4 };
		assert(list10.size() == 5);
		int val1 = 0;
		for (SList<int>::iterator i = list10.begin(); i != list10.end(); ++i, ++val1)
		{
			assert(*i == val1);
		}

		std::cout << std::endl << "not empty ...";
		assert(!list10.empty());

		std::cout << std::endl << "push front ...";
		list10.push_front(-1);
		assert(list10.size() == 6);
		int val2 = -1;
		for (SList<int>::iterator i = list10.begin(); i != list10.end(); ++i, ++val2)
		{
			assert(*i == val2);
		}

		std::cout << std::endl << "push front move ...";
		int val4 = -2;
		list10.push_front(std::move(val4));
		assert(list10.size() == 7);
		int val3 = -2;
		for (SList<int>::iterator i = list10.begin(); i != list10.end(); ++i, ++val3)
		{
			assert(*i == val3);
		}
		assert(val4 == 0);


		std::cout << std::endl << "pop front ...";
		list10.pop_front();
		assert(list10.size() == 6);
		int val5 = -1;
		for (SList<int>::iterator i = list10.begin(); i != list10.end(); ++i, ++val5)
		{
			assert(*i == val5);
		}

		std::cout << std::endl << "push back move ...";
		int val6 = 5;
		list10.push_back(std::move(val6));
		assert(list10.size() == 7);
		int val7 = -1;
		for (SList<int>::iterator i = list10.begin(); i != list10.end(); ++i, ++val7)
		{
			assert(*i == val7);
		}

		std::cout << std::endl;
	}


	// TESTING SArrayLIST modifiers
	{


		std::cout << std::endl << std::endl << "SArrayLIST modifiers //////////////////////////////////////////////////////////////////////////////////// " << std::endl;

		SListArray<int>list6(11, 5);

		std::cout << std::endl << "operator= ...";
		SListArray<int>list8 = list6;
		assert(list8.size() == 11);
		for (SListArray<int>::iterator i = list8.begin(); i != list8.end(); ++i)
		{
			assert(*i == 5);
		}

		std::cout << std::endl << "operator= move ...";
		SListArray<int>list9 = std::move(list6);
		assert(list9.size() == 11);
		for (SListArray<int>::iterator i = list9.begin(); i != list9.end(); ++i)
		{
			assert(*i == 5);
		}
		assert(list6.size() == 0);


		std::cout << std::endl << "operator= inizializer list ...";
		SListArray<int>list10 = { 0,1,2,3,4 };
		assert(list10.size() == 5);
		int val1 = 0;
		for (SListArray<int>::iterator i = list10.begin(); i != list10.end(); ++i, ++val1)
		{
			assert(*i == val1);
		}

		std::cout << std::endl << "not empty ...";
		assert(!list10.empty());

		std::cout << std::endl << "push front ...";
		list10.push_front(-1);
		assert(list10.size() == 6);
		int val2 = -1;
		for (SListArray<int>::iterator i = list10.begin(); i != list10.end(); ++i, ++val2)
		{
			assert(*i == val2);
		}

		std::cout << std::endl << "push front move ...";
		int val4 = -2;
		list10.push_front(std::move(val4));
		assert(list10.size() == 7);
		int val3 = -2;
		for (SListArray<int>::iterator i = list10.begin(); i != list10.end(); ++i, ++val3)
		{
			assert(*i == val3);
		}
		assert(val4 == 0);


		std::cout << std::endl << "pop front ...";
		list10.pop_front();
		assert(list10.size() == 6);
		int val5 = -1;
		for (SListArray<int>::iterator i = list10.begin(); i != list10.end(); ++i, ++val5)
		{
			assert(*i == val5);
		}

		std::cout << std::endl << "push back move ...";
		int val6 = 5;
		list10.push_back(std::move(val6));
		assert(list10.size() == 7);
		int val7 = -1;
		for (SListArray<int>::iterator i = list10.begin(); i != list10.end(); ++i, ++val7)
		{
			assert(*i == val7);
		}

		std::cout << std::endl;
	}


	char end;
	std::cout << std::endl << "Press any char and ENTER to quit :";
	std::cin >> end;

	return 0;
}