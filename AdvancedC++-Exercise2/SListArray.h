#pragma once

#include "ListNode.h"
#include "SListIterator.h"
#include <iterator>
#include <vector>


namespace list {


template<class T>
class SListArray
{

public:

	typedef T value_type;
	typedef T& reference_type;
	typedef const T& const_reference_type;

	typedef SListIterator<ListNode<T>> iterator;
	typedef SListIterator<const ListNode<T>> const_iterator;
	typedef std::reverse_iterator<SListIterator<T>> reverse_iterator;
	typedef std::reverse_iterator<const SListIterator<T>> const_reverse_iterator;

	SListArray()
	{
		_Root = nullptr;
		_Size = 0;
	};

	explicit SListArray(size_t n)
	{
		value_type val = {};
		SListArray(n, val);
	};

	SListArray(size_t n, const value_type& val)
	{
		_Data = new std::vector<ListNode<T>>(n);
		_Size = n;
		if (n > 0)
		{
			_Data[0].value=val;
			_Data[0].next = nullptr;
			_Root = &_Data[0];
		}
		for (size_t i=1; i < n; ++i)
		{
			_Data[i-1].next = &_Data[i];
			_Data[i].value = val;
			_Data[i].next = nullptr;
		}
	};

	SListArray(iterator first, iterator last)
	{
		_Data = new std::vector<ListNode<T>>(last - first);
		if (first != last)
		{
			_Data[0].value = *first;
			_Data[0].next = nullptr;
			_Root = &_Data[0];
			_Size = 1;
			first++;
		}
		for (; first != last; ++first,++_Size)
		{
			_Data[_Size-1].next = &_Data[_Size];
			_Data[_Size].value = *first;
			_Data[_Size].next = nullptr;
		}
	};

	SListArray(const SListArray& x)
	{
		_Size = x._Size;
		_Data = new std::vector<ListNode<T>>(_Size);
		iterator it = x.begin();
		if (_Size > 0)
		{
			_Data[0].value = x._Data[0];
			_Data[0].next = nullptr;
			_Root = &_Data[0];
		}
		for (int i = 1; i < x._Size; ++i, ++it)
		{
			_Data[i - 1].next = &_Data[i];
			_Data[i].value = x._Data[i];
			_Data[i].next = nullptr;
		}
	};

	SListArray(SListArray&& x)
	{
		_Root = x._Root;
		_Size = x._Size;
		_Data = x._Data;
		x._Data = new std::vector<ListNode<T>>();
		x._Root = nullptr;
		x._Size = 0;
	};

	SListArray(std::initializer_list<value_type> il)
	{
		_Root = nullptr;
		const value_type* it = il.begin(); //equivalent of std::initializer_list<value_type>::iterator
		_Size = il.size();
		_Data = new std::vector<ListNode<T>>(il.size());
		if (_Size > 0)
		{
			_Data[0].value = *it;
			_Data[0].next = nullptr;
			_Root = &_Data[0]; 
			++it;
		}
		for (size_t i=1; it != il.end(); ++it,++i)
		{
			_Data[i-1].next = &_Data[i - 1];
			_Data[i].value = *it;
			_Data[i].next = nullptr;
		}
	};

	virtual ~SListArray()
	{
		_Size = 0;
		_Root = nullptr;
	};

	SListArray& operator= (const SListArray& x)
	{
		_Size = 0;
		_Root = nullptr;

		SListArray aux(x);
		std::swap(*this, aux);
		return *this;
	};

	SListArray& operator= (SListArray&& x)
	{
		_Size = 0;
		_Root = nullptr;

		std::swap(*this, x);
		return *this;
	};

	SListArray& operator= (std::initializer_list<value_type> il)
	{
		_Size = 0;
		_Root = nullptr;

		SListArray aux(il);
		std::swap(*this, aux);
		return *this;
	};

	bool empty() const
	{
		return _Size < 0;
	};

	size_t size() const
	{
		return _Size;
	};

	void push_front(const value_type& val)
	{
		_Data.insert(0, { val,_Root });
		_Root = &_Data[0];
		++_Size;
	};

	void push_front(value_type&& val)
	{
		ListNode<T> newNode{ val,_Root };
		//std::swap(newNode.val, val);
		_Data.insert(0, newNode);
		_Root = &_Data[0];
		++_Size;
	};

	void pop_front()
	{
		if (_Size > 0)
		{
			_Data[0].value.~value_type();
			_Data.erase(_Data.begin());
			_Root = &_Data[0];
			--_Size;
		}
	};

	void push_back(const value_type& val)
	{
		_Data.push_back({ val,nullptr });
		++_Size;
		if (_Size > 1)
		{
			_Data[_Size - 2].next = _Data[_Size - 1];
		}
	};

	void push_back(value_type&& val)
	{
		ListNode<T> newNode{val, nullptr};
		//std::swap(newNode.val, val);
		_Data.push_back({ newNode });
		++_Size;
		if (_Size > 1)
		{
			_Data[_Size - 2].next = &_Data[_Size - 1];
		}
	};

	iterator begin() 
	{ 
		return iterator(_Root); 
	};

	iterator end() 
	{ 
		return iterator(nullptr); 
	};

	const_iterator cbegin() const 
	{ 
		return const_iterator(_Root); 
	};

	const_iterator cend() const 
	{ 
		return const_iterator(nullptr); 
	};

private:

	ListNode<T>* _Root;

	std::vector<ListNode<T>> _Data;

	size_t _Size;

};


} // namespace list

