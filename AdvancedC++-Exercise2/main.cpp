#include "SList.h"
#include "SListArray.h"
#include "FixedSList.h"
#include <iostream>
#include <cassert>

using namespace list;

void PrintListOfInt(SList<int>& list)
{
	SList<int>::iterator siterator = list.begin();

	if (!(siterator != list.end()))
	{
		std::cout << "List Empty!" << std::endl;
	}
	else
	{
		for (siterator; siterator != list.end(); siterator++)
			std::cout << siterator.GetNode().value << " ";
		std::cout << std::endl;
	}
}

void PrintListOfInt(SListArray<int>& list)
{
	SListArray<int>::iterator siterator = list.begin();

	if (list.size() == 0)
	{
		std::cout << "List Empty!" << std::endl;
	}
	else
	{
		for (siterator; siterator != list.end(); siterator++)
			std::cout << siterator.GetNode().value << " ";
		std::cout << std::endl;
	}
}


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

	// TESTING FixesSList CONSTRUCTORS
	{



		std::cout << std::endl << std::endl << "FixesSList constructors ////////////////////////////////////////////////////////////////////////////////////" << std::endl;

		// FixedSList
		std::cout << "FixedSList default constructor... ";
		FixedSList<int, 1> flist;
		std::cout << "OK!" << std::endl;

		std::cout << "fill constructor... ";
		FixedSList<int,12>list2(12);
		assert(list2.size() == 12);

		std::cout << std::endl << "fill constructor with val ...";
		FixedSList<int,12>list3(12, 5);
		assert(list3.size() == 12);
		for (FixedSList<int,12>::iterator i = list3.begin(); i != list3.end(); ++i)
		{
			assert(*i == 5);
		}


		std::cout << std::endl << "iterator constructor ...";
		FixedSList<int,11>list4(++list3.begin(), list3.end());
		assert(list4.size() == 11);
		for (FixedSList<int,11>::iterator i = list4.begin(); i != list4.end(); ++i)
		{
			assert(*i == 5);
		}


		std::cout << std::endl << "copy constructor ...";
		FixedSList<int,11>list5(list4);
		assert(list5.size() == 11);
		for (FixedSList<int,11>::iterator i = list5.begin(); i != list5.end(); ++i)
		{
			assert(*i == 5);
		}

		std::cout << std::endl << "move constructor ...";
		FixedSList<int,11>list6(std::move(list4));
		assert(list6.size() == 11);
		for (FixedSList<int,11>::iterator i = list6.begin(); i != list6.end(); ++i)
		{
			assert(*i == 5);
		}
		assert(list4.size() == 0);

		std::cout << std::endl << "inizializer list constructor ...";
		FixedSList<int,5>list7{ 0,1,2,3,4 };
		assert(list7.size() == 5);
		int val = 0;
		for (FixedSList<int,5>::iterator i = list7.begin(); i != list7.end(); ++i, ++val)
		{
			assert(*i == val);
		}

		std::cout << std::endl << "destructor ...";
		list7.~FixedSList<int,5>();
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

		int val4 = -1;
		std::cout << std::endl << "push front ...";
		list10.push_front(val4);
		assert(list10.size() == 6);
		int val2 = -1;
		for (SList<int>::iterator i = list10.begin(); i != list10.end(); ++i, ++val2)
		{
			assert(*i == val2);
		}

		std::cout << std::endl << "push front move ...";
		val4 = -2;
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
		list10.push_back(val6);
		assert(list10.size() == 7);
		int val7 = -1;
		for (SList<int>::iterator i = list10.begin(); i != list10.end(); ++i, ++val7)
		{
			assert(*i == val7);
		}


		std::cout << std::endl << "push back move ...";
		val6 = 6;
		list10.push_back(std::move(val6));
		assert(list10.size() == 8);
		val7 = -1;
		for (SList<int>::iterator i = list10.begin(); i != list10.end(); ++i, ++val7)
		{
			assert(*i == val7);
		}
		
		
		std::cout << std::endl << "pop back ...";
		list10.pop_back();
		assert(list10.size() == 7);
		int val8 = -1;
		for (SList<int>::iterator i = list10.begin(); i != list10.end(); ++i, ++val8)
		{
			assert(*i == val8);
		}


		std::cout << std::endl;


		std::cout << "Member access: front = " << list10.front().value << std::endl;
		std::cout << "Member access: back = " << list10.back().value << std::endl;


		std::cout << std::endl << "insert begin() ... ";
		SList<int>::iterator siterator = list10.begin();
		list10.insert(siterator, -2);
		assert(list10.size() == 8);
		int val9 = -2;
		for (SList<int>::iterator i = list10.begin(); i != list10.end(); ++i, ++val9)
		{
			assert(*i == val9);
		}
		std::cout << "List : ";
		PrintListOfInt(list10);

		std::cout << std::endl << "insert at end()... ";
		SList<int>::iterator siterator2 = list10.end();
		list10.insert(siterator2, 6);
		assert(list10.size() == 9);
		int val10 = -2;
		for (SList<int>::iterator i = list10.begin(); i != list10.end(); ++i, ++val10)
		{
			assert(*i == val10);
		}
		std::cout << "List : ";
		PrintListOfInt(list10);


		std::cout << std::endl << "insert at pos[3] ... ";
		SList<int>::iterator siterator3 = list10.begin();
		siterator3++;
		siterator3++;
		siterator3++;
		list10.insert(siterator3, 1000);
		assert(list10.size() == 10);
		std::cout << "List : ";
		PrintListOfInt(list10);

		std::cout << std::endl << "erase at pos[3] ... ";
		SList<int>::iterator siterator4 = list10.begin();
		siterator4++;
		siterator4++;
		siterator4++;
		list10.erase(siterator4);
		assert(list10.size() == 9);
		int val11 = -2;
		for (SList<int>::iterator i = list10.begin(); i != list10.end(); ++i, ++val11)
		{
			assert(*i == val11);
		}
		std::cout << "List : ";
		PrintListOfInt(list10);


		std::cout << std::endl << "erase from pos[1] to [7] ... ";
		SList<int>::iterator siterator5 = list10.begin();
		SList<int>::iterator siterator6 = list10.begin();
		// siterator5 + 1
		siterator5++;
		// siterator6 + 7
		siterator6++;
		siterator6++;
		siterator6++;
		siterator6++;
		siterator6++;
		siterator6++;
		siterator6++;
		list10.erase(siterator5, siterator6);
		assert(list10.size() == 2);
		std::cout << "List : ";
		PrintListOfInt(list10);


		std::cout << std::endl << "resize count = 5 ... ";
		int newSize = 5;
		list10.resize(newSize);
		assert(list10.size() == newSize);
		std::cout << "List : ";
		PrintListOfInt(list10);


		std::cout << std::endl << "clear list ... ";
		list10.clear();
		assert(list10.size() == 0);
		std::cout << "List : ";
		PrintListOfInt(list10);


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

		int val4 = -1;
		std::cout << std::endl << "push front ...";
		list10.push_front(val4);
		assert(list10.size() == 6);
		int val2 = -1;
		for (SListArray<int>::iterator i = list10.begin(); i != list10.end(); ++i, ++val2)
		{
			assert(*i == val2);
		}

		std::cout << std::endl << "push front move ...";
		val4 = -2;
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

		std::cout << std::endl << "push back ...";
		int val6 = 5;
		list10.push_back(val6);
		assert(list10.size() == 7);
		int val7 = -1;
		for (SListArray<int>::iterator i = list10.begin(); i != list10.end(); ++i, ++val7)
		{
			assert(*i == val7);
		}


		std::cout << std::endl << "push back move ...";
		val6 = 6;
		list10.push_back(std::move(val6));
		assert(list10.size() == 8);
		val7 = -1;
		for (SListArray<int>::iterator i = list10.begin(); i != list10.end(); ++i, ++val7)
		{
			assert(*i == val7);
		}



		// To be tested
		std::cout << std::endl << "pop back ...";
		list10.pop_back();
		assert(list10.size() == 7);
		int val8 = -1;
		for (SListArray<int>::iterator i = list10.begin(); i != list10.end(); ++i, ++val8)
		{
			assert(*i == val8);
		}

		PrintListOfInt(list10);


		std::cout << std::endl;


		std::cout << "Member access: front = " << list10.front().value << std::endl;
		std::cout << "Member access: back = " << list10.back().value << std::endl;


		std::cout << std::endl << "insert begin() ... ";
		SListArray<int>::iterator siterator = list10.begin();
		list10.insert(siterator, -2);
		assert(list10.size() == 8);
		int val9 = -2;
		for (SListArray<int>::iterator i = list10.begin(); i != list10.end(); ++i, ++val9)
		{
			assert(*i == val9);
		}
		std::cout << "List : ";
		PrintListOfInt(list10);

		std::cout << std::endl << "insert at end()... ";
		SListArray<int>::iterator siterator2 = list10.end();
		list10.insert(siterator2, 6);
		assert(list10.size() == 9);
		int val10 = -2;
		for (SListArray<int>::iterator i = list10.begin(); i != list10.end(); ++i, ++val10)
		{
			assert(*i == val10);
		}
		std::cout << "List : ";
		PrintListOfInt(list10);


		std::cout << std::endl << "insert at pos[3] ... ";
		SListArray<int>::iterator siterator3 = list10.begin();
		siterator3++;
		siterator3++;
		siterator3++;
		list10.insert(siterator3, 1000);
		assert(list10.size() == 10);
		std::cout << "List : ";
		PrintListOfInt(list10);

		std::cout << std::endl << "erase at pos[3] ... ";
		SListArray<int>::iterator siterator4 = list10.begin();
		siterator4++;
		siterator4++;
		siterator4++;
		list10.erase(siterator4);
		assert(list10.size() == 9);
		int val11 = -2;
		for (SListArray<int>::iterator i = list10.begin(); i != list10.end(); ++i, ++val11)
		{
			assert(*i == val11);
		}
		std::cout << "List : ";
		PrintListOfInt(list10);


		std::cout << std::endl << "erase from pos[1] to [7] ... ";
		SListArray<int>::iterator siterator5 = list10.begin();
		SListArray<int>::iterator siterator6 = list10.begin();
		// siterator5 + 1
		siterator5++;
		// siterator6 + 7
		siterator6++;
		siterator6++;
		siterator6++;
		siterator6++;
		siterator6++;
		siterator6++;
		siterator6++;
		list10.erase(siterator5, siterator6);
		assert(list10.size() == 2);
		std::cout << "List : ";
		PrintListOfInt(list10);


		std::cout << std::endl << "resize count = 5 ... ";
		int newSize = 5;
		list10.resize(newSize);
		assert(list10.size() == newSize);
		std::cout << "List : ";
		PrintListOfInt(list10);


		std::cout << std::endl << "clear list ... ";
		list10.clear();
		assert(list10.size() == 0);
		std::cout << "List : ";
		PrintListOfInt(list10);


		std::cout << std::endl;
	}


	// TESTING FixedSList modifiers
	{


		std::cout << std::endl << std::endl << "FixedSList modifiers //////////////////////////////////////////////////////////////////////////////////// " << std::endl;

		FixedSList<int,11>list6(11, 5);

		std::cout << std::endl << "operator= ...";
		FixedSList<int, 11>list8 = list6;
		assert(list8.size() == 11);
		for (FixedSList<int, 11>::iterator i = list8.begin(); i != list8.end(); ++i)
		{
			assert(*i == 5);
		}

		std::cout << std::endl << "operator= move ...";
		FixedSList<int, 11>list9 = std::move(list6);
		assert(list9.size() == 11);
		for (FixedSList<int, 11>::iterator i = list9.begin(); i != list9.end(); ++i)
		{
			assert(*i == 5);
		}
		assert(list6.size() == 0);


		std::cout << std::endl << "operator= inizializer list ...";
		FixedSList<int, 8>list10 = { 0,1,2,3,4 };
		assert(list10.size() == 5);
		int val1 = 0;
		for (FixedSList<int, 8>::iterator i = list10.begin(); i != list10.end(); ++i, ++val1)
		{
			assert(*i == val1);
		}

		std::cout << std::endl << "not empty ...";
		assert(!list10.empty());
		int val4 = -1;

		std::cout << std::endl << "push front ...";
		list10.push_front(val4);
		assert(list10.size() == 6);
		int val2 = -1;
		for (FixedSList<int, 8>::iterator i = list10.begin(); i != list10.end(); ++i, ++val2)
		{
			assert(*i == val2);
		}

		val4 = -2;

		std::cout << std::endl << "push front move ...";
		list10.push_front(std::move(val4));
		assert(list10.size() == 7);
		int val3 = -2;
		for (FixedSList<int, 8>::iterator i = list10.begin(); i != list10.end(); ++i, ++val3)
		{
			assert(*i == val3);
		}
		assert(val4 == -1);


		std::cout << std::endl << "pop front ...";
		list10.pop_front();
		assert(list10.size() == 6);
		int val5 = -1;
		for (FixedSList<int, 8>::iterator i = list10.begin(); i != list10.end(); ++i, ++val5)
		{
			assert(*i == val5);
		}

		std::cout << std::endl << "push back ...";
		int val6 = 5;
		list10.push_back(val6);
		assert(list10.size() == 7);
		int val7 = -1;
		for (FixedSList<int, 8>::iterator i = list10.begin(); i != list10.end(); ++i, ++val7)
		{
			assert(*i == val7);
		}

		std::cout << std::endl << "push back move ...";
		val6 = 6;
		list10.push_back(std::move(val6));
		assert(list10.size() == 8);
		val7 = -1;
		for (FixedSList<int, 8>::iterator i = list10.begin(); i != list10.end(); ++i, ++val7)
		{
			assert(*i == val7);
		}


		// To be tested
		//std::cout << std::endl << "pop back ...";
		//list10.pop_back();
		//assert(list10.size() == 7);
		//int val8 = -1;
		//for (FixedSList<int>::iterator i = list10.begin(); i != list10.end(); ++i, ++val8)
		//{
		//	assert(*i == val8);
		//}


		//std::cout << std::endl;


		//std::cout << "Member access: front = " << list10.front().value << std::endl;
		//std::cout << "Member access: back = " << list10.back().value << std::endl;


		//std::cout << std::endl << "insert begin() ... ";
		//FixedSList<int>::iterator siterator = list10.begin();
		//list10.insert(siterator, -2);
		//assert(list10.size() == 8);
		//int val9 = -2;
		//for (FixedSList<int>::iterator i = list10.begin(); i != list10.end(); ++i, ++val9)
		//{
		//	assert(*i == val9);
		//}
		//std::cout << "List : ";
		//PrintListOfInt(list10);

		//std::cout << std::endl << "insert at end()... ";
		//FixedSList<int>::iterator siterator2 = list10.end();
		//list10.insert(siterator2, 6);
		//assert(list10.size() == 9);
		//int val10 = -2;
		//for (FixedSList<int>::iterator i = list10.begin(); i != list10.end(); ++i, ++val10)
		//{
		//	assert(*i == val10);
		//}
		//std::cout << "List : ";
		//PrintListOfInt(list10);


		//std::cout << std::endl << "insert at pos[3] ... ";
		//FixedSList<int>::iterator siterator3 = list10.begin();
		//siterator3++;
		//siterator3++;
		//siterator3++;
		//list10.insert(siterator3, 1000);
		//assert(list10.size() == 10);
		//std::cout << "List : ";
		//PrintListOfInt(list10);

		//std::cout << std::endl << "erase at pos[3] ... ";
		//FixedSList<int>::iterator siterator4 = list10.begin();
		//siterator4++;
		//siterator4++;
		//siterator4++;
		//list10.erase(siterator4);
		//assert(list10.size() == 9);
		//int val11 = -2;
		//for (FixedSList<int>::iterator i = list10.begin(); i != list10.end(); ++i, ++val11)
		//{
		//	assert(*i == val11);
		//}
		//std::cout << "List : ";
		//PrintListOfInt(list10);


		//std::cout << std::endl << "erase from pos[1] to [7] ... ";
		//FixedSList<int>::iterator siterator5 = list10.begin();
		//FixedSList<int>::iterator siterator6 = list10.begin();
		//// siterator5 + 1
		//siterator5++;
		//// siterator6 + 7
		//siterator6++;
		//siterator6++;
		//siterator6++;
		//siterator6++;
		//siterator6++;
		//siterator6++;
		//siterator6++;
		//list10.erase(siterator5, siterator6);
		//assert(list10.size() == 2);
		//std::cout << "List : ";
		//PrintListOfInt(list10);


		//std::cout << std::endl << "resize count = 10 ... ";
		//int newSize = 5;
		//list10.resize(newSize);
		//assert(list10.size() == newSize);
		//std::cout << "List : ";
		//PrintListOfInt(list10);


		//std::cout << std::endl << "clear list ... ";
		//list10.clear();
		//assert(list10.size() == 0);
		//std::cout << "List : ";
		//PrintListOfInt(list10);


		std::cout << std::endl;
	}


	char end;
	std::cout << std::endl << "Press any char and ENTER to quit :";
	std::cin >> end;

	return 0;
}