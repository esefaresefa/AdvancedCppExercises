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
		assert(*i == 5);
	}

	SList<int>list4(++list3.begin(), list3.end());
	assert(list4.size() == 11);
	for (SList<int>::iterator i = list4.begin(); i != list4.end(); ++i)
	{
		assert(*i == 5);
	}


	SList<int>list5(list4);
	assert(list5.size() == 11);
	for (SList<int>::iterator i = list5.begin(); i != list5.end(); ++i)
	{
		assert(*i == 5);
	}

	SList<int>list6(std::move(list4));
	assert(list6.size() == 11);
	for (SList<int>::iterator i = list6.begin(); i != list6.end(); ++i)
	{
		assert(*i == 5);
	}
	assert(list4.size() == 0);

	SList<int>list7{0,1,2,3,4};
	assert(list7.size() == 5);
	int val = 0;
	for (SList<int>::iterator i = list7.begin(); i != list7.end(); ++i, ++val)
	{
		assert(*i == val);
	}

	list7.~SList<int>();
	assert(list7.size() == 0);
	assert(list7.empty());



	SList<int>list8=list6;
	assert(list8.size() == 11);
	for (SList<int>::iterator i = list8.begin(); i != list8.end(); ++i)
	{
		assert(*i == 5);
	}

	SList<int>list9=std::move(list6);
	assert(list9.size() == 11);
	for (SList<int>::iterator i = list9.begin(); i != list9.end(); ++i)
	{
		assert(*i == 5);
	}
	assert(list6.size() == 0);


	SList<int>list10={ 0,1,2,3,4 };
	assert(list10.size() == 5);
	int val1 = 0;
	for (SList<int>::iterator i = list10.begin(); i != list10.end(); ++i, ++val1)
	{
		assert(*i == val1);
	}

	assert(!list10.empty());

	list10.push_front (-1);
	assert(list10.size() == 6);
	int val2 = -1;
	for (SList<int>::iterator i = list10.begin(); i != list10.end(); ++i, ++val2)
	{
		assert(*i == val2);
	}
	int val4 = -2;
	list10.push_front(std::move(val4));
	assert(list10.size() == 7);
	int val3 = -2;
	for (SList<int>::iterator i = list10.begin(); i != list10.end(); ++i, ++val3)
	{
		assert(*i == val3);
	}
	assert(val4 == 0);

	list10.pop_front();
	assert(list10.size() == 6);
	int val5 = -1;
	for (SList<int>::iterator i = list10.begin(); i != list10.end(); ++i, ++val5)
	{
		assert(*i == val5);
	}

	int val6 = 5;
	list10.push_back(std::move(val6));
	assert(list10.size() == 7);
	int val7 = -1;
	for (SList<int>::iterator i = list10.begin(); i != list10.end(); ++i, ++val7)
	{
		assert(*i == val7);
	}

	std::cout << std::endl;


	char end;
	std::cout << std::endl << "Press any char and ENTER to quit :";
	std::cin >> end;

	return 0;
}