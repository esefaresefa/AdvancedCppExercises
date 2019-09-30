#pragma once

#include "SListIterator.h"
#include "ListNode.h"
#include <iterator>


namespace list {

	   	  
template<typename T>
class SList
{

public:

	typedef T value_type;
	typedef T& reference_type;
	typedef const T& const_reference_type;

	typedef SListIterator<ListNode<T>> iterator;
	typedef SListIterator<const ListNode<T>> const_iterator;
	typedef std::reverse_iterator<SListIterator<T>> reverse_iterator;
	typedef std::reverse_iterator<const SListIterator<T>> const_reverse_iterator;
	
	explicit SList() 
	{
		_Root = nullptr;
		_Size = 0;
	};

	explicit SList(size_t n)
	{
		value_type val = {};
		SList aux(n, val);
		std::swap(*this, aux);
	};

	SList(size_t n, const value_type& val)
	{
		_Root = nullptr;
		ListNode<T>* AuxNode = nullptr;
		_Size = n;
		if (n > 0)
		{
			_Root = new ListNode<T>();
			_Root->value = val;
			_Root->next = nullptr;
			AuxNode = _Root;
			--n;
		}
		for (; n > 0; --n)
		{
			AuxNode->next = new ListNode<T>();
			AuxNode = AuxNode->next;
			AuxNode->value = val;
		}
		AuxNode->next = nullptr;
	};

	SList(iterator first, iterator last)
	{
		_Root = new ListNode<T>();
		_Root->value = *first;
		_Root->next = nullptr;
		_Size = 1;
		ListNode<T>* AuxNode = _Root;
		first++;
		for (;first!=last;++first,++_Size)
		{
			AuxNode->next = new ListNode<T>();
			AuxNode = AuxNode->next;
			AuxNode->value = *first;
		}
		AuxNode->next = nullptr;
	};

	SList(const SList& x)
	{
		_Root = nullptr;
		ListNode<T>* AuxNode = _Root;
		const_iterator it = x.cbegin();
		_Size = x._Size;
		if (_Size > 0)
		{
			_Root = new ListNode<T>();
			_Root->value = *it;
			_Root->next = nullptr;
			AuxNode = _Root;
		}
		for (int i=1; i < x._Size; ++i, ++it)
		{
			AuxNode->next = new ListNode<T>();
			AuxNode = AuxNode->next;
			AuxNode->value = *it;
		}
		AuxNode->next = nullptr;
	};

	SList(SList&& x)
	{
		std::swap(_Root, x._Root);
		std::swap(_Size, x._Size);
	};

	SList(std::initializer_list<value_type> il)
	{
		_Root = nullptr;
		ListNode<T>* AuxNode = _Root;
		const value_type* it = il.begin(); //equivalent of std::initializer_list<value_type>::iterator
		_Size = il.size();
		if (il.size()>0)
		{
			_Root = new ListNode<T>();
			_Root->value = *it;
			_Root->next = nullptr;
			AuxNode = _Root; 
			++it;
		}
		for (; it != il.end(); ++it)
		{
			AuxNode->next = new ListNode<T>();
			AuxNode = AuxNode->next;
			AuxNode->value = *it;
		}
		AuxNode->next = nullptr;
	};

	virtual ~SList() 
	{
		ListNode<T>* AuxNode = nullptr;
		for (; _Size > 0; _Size--)
		{
			AuxNode = _Root;
			_Root = _Root->next;
			AuxNode->value.~value_type();
			delete AuxNode;
		}
		delete _Root;
	};

	SList& operator= (const SList& x)
	{
		ListNode<T>* AuxNode = nullptr;
		for (; _Size > 0; _Size--)
		{
			AuxNode = _Root;
			_Root = _Root->next;
			AuxNode->value.~value_type();
			delete AuxNode;
		}
		SList aux(x);
		std::swap(*this, aux);
		return *this;
	};

	SList& operator= (SList&& x) 
	{
		ListNode<T>* AuxNode = nullptr;
		for (; _Size > 0; _Size--)
		{
			AuxNode = _Root;
			_Root = _Root->next;
			AuxNode->value.~value_type();
			delete AuxNode;
		}
		std::swap(*this, x);
		return *this;
	};

	SList& operator= (std::initializer_list<value_type> il)
	{
		ListNode<T>* AuxNode = nullptr;
		for (; _Size > 0; _Size--)
		{
			AuxNode = _Root;
			_Root = _Root->next;
			AuxNode->value.~value_type();
			delete AuxNode;
		}
		SList aux(il);
		std::swap(*this, aux);
		return *this;
	};

	bool empty() const 
	{
		return _Size <= 0;
	};

	size_t size() const
	{
		return _Size;
	};

	void push_front(const value_type& val)
	{
		ListNode<T>* NewElement = new ListNode<T>();
		NewElement->value = val;
		NewElement->next = _Root;
		_Root = NewElement;
		++_Size;
	};

	void push_front(value_type&& val) 
	{
		ListNode<T>* NewElement = new ListNode<T>();
		std::swap(NewElement->value, val);
		NewElement->next = _Root;
		_Root = NewElement;
		++_Size;
	};

	void pop_front() 
	{
		if (_Size > 0)
		{
			ListNode<T>* AuxNode = _Root;
			_Root = _Root->next;
			--_Size;
			AuxNode->value.~value_type();
			delete AuxNode;
		}
	};

	void push_back(const value_type& val)
	{
		if (_Size > 0)
		{
			ListNode<T>* NewElement = GetLast();

			NewElement->next = new ListNode<T>();
			NewElement = NewElement->next;
			NewElement->value = val;
			NewElement->next = nullptr;
			++_Size;
		}
		else
		{
			_Root = new ListNode<T>();
			_Root->value = val;
			_Root->next = nullptr;
			++_Size;
		}
	};

	void push_back(value_type&& val) 
	{
		if (_Size > 0)
		{
			ListNode<T>* NewElement = GetLast();

			NewElement->next = new ListNode<T>();
			NewElement = NewElement->next;
			std::swap(NewElement->value, val);
			NewElement->next = nullptr;
			++_Size;
		}
		else
		{
			_Root = new ListNode<T>();
			std::swap(_Root->value , val);
			_Root->next = nullptr;
			++_Size;
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

	reverse_iterator rbegin()
	{
		return reverse_iterator(_Root);
	};

	const_reverse_iterator rend() const
	{
		return const_reverse_iterator(nullptr);
	};

protected:

	ListNode<T>* GetLast() 
	{
		ListNode<T>* Element = _Root;
		while (Element->next)
		{
			Element = Element->next;
		}
		return Element;
	}

private:

	ListNode<T>* _Root;
	size_t _Size;

};



} // namespace list