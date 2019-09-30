#pragma once

#include "SListIterator.h"
#include "SListNode.h"
#include <iterator>


namespace slist {

	   	  
template<typename T>
class SList
{

public:

	typedef T value_type;
	typedef T& reference_type;
	typedef const T& const_reference_type;

	typedef SListIterator<SListNode<T>> iterator;
	typedef SListIterator<const SListNode<T>> const_iterator;
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
		SList(n, val);
	};

	SList(size_t n, const value_type& val)
	{
		_Root = nullptr;
		SListNode* AuxNode = nullptr;
		_Size = n;
		if (n > 0)
		{
			_Root = new SListNode();
			_Root->value = val;
			_Root->next = nullptr;
			AuxNode = _Root;
			--n;
		}
		for (; n > 0; --n)
		{
			AuxNode->next = new SListNode();
			AuxNode = AuxNode->next;
			AuxNode->value = val;
		}
		AuxNode->next = nullptr;
	};

	SList(iterator first, iterator last)
	{
		_Root = new SListNode();
		_Root->value = *first;
		_Root->next = nullptr;
		_Size = 1;
		SListNode* AuxNode = _Root;
		first++;
		for (;first!=last;++first)
		{
			AuxNode->next = new SListNode();
			AuxNode = AuxNode->next;
			AuxNode->value = *first;
			++_Size;
		}
		AuxNode->next = nullptr;
	};

	SList(const SList& x)
	{
		_Root = nullptr;
		SListNode* AuxNode = _Root;
		iterator it = x.begin();
		_Size = x._Size;
		if (_Size > 0)
		{
			_Root = new SListNode();
			_Root->value = *it;
			_Root->next = nullptr;
			AuxNode = _Root;
		}
		for (int i=1; i < x._Size; ++i, ++it)
		{
			AuxNode->next = new SListNode();
			AuxNode = AuxNode->next;
			AuxNode->value = *it;
		}
		AuxNode->next = nullptr;
	};

	SList(SList&& x)
	{
		_Root = x._Root;
		_Size = x._Size;
		x._Root = nullptr;
		x._Size = 0;
	};

	SList(std::initializer_list<value_type> il)
	{
		_Root = nullptr;
		SListNode* AuxNode = _Root;
		const value_type* it = il.begin(); //equivalent of std::initializer_list<value_type>::iterator
		_Size = il.size();
		if (il.size()>0)
		{
			_Root = new SListNode();
			_Root->value = *it;
			_Root->next = nullptr;
			AuxNode = _Root; 
			++it;
		}
		for (; it != il.end(); ++it)
		{
			AuxNode->next = new SListNode();
			AuxNode = AuxNode->next;
			AuxNode->value = *it;
		}
		AuxNode->next = nullptr;
	};

	virtual ~SList() 
	{
		SListNode<T>* AuxNode = nullptr;
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
		SListNode* AuxNode = nullptr;
		for (; _Size > 0; _Size--)
		{
			AuxNode = _Root;
			_Root = _Root->next;
			AuxNode->value.~value_type();
			delete AuxNode;
		}
		SList aux(x);
		std::swap(_Root,aux._Root);
		std::swap(_Size,aux._Size);
		return *this;
	};

	SList& operator= (SList&& x) 
	{
		SListNode* AuxNode=nullptr;
		for (; _Size > 0; _Size--)
		{
			AuxNode = _Root;
			_Root = _Root->next;
			AuxNode->value.~value_type();
			delete AuxNode;
		}
		std::swap(_Root, x);
		std::swap(_Size, x);
		return *this;
	};

	SList& operator= (std::initializer_list<value_type> il)
	{
		SListNode* AuxNode = nullptr;
		for (; _Size > 0; _Size--)
		{
			AuxNode = _Root;
			_Root = _Root->next;
			AuxNode->value.~value_type();
			delete AuxNode;
		}
		SList aux(il);
		std::swap(_Root, aux._Root);
		std::swap(_Size, aux._Size);
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
		SListNode* NewElement = new SListNode();
		NewElement->value = val;
		NewElement->next = _Root;
		_Root = NewElement;
		++_Size;
	};

	void push_front(value_type&& val) 
	{
		SListNode* NewElement = new SListNode();
		std::swap(NewElement->value, val);
		NewElement->next = _Root;
		_Root = NewElement;
		++_Size;
	};

	void pop_front() 
	{
		if (_Size > 0)
		{
			SListNode* AuxNode = _Root;
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
			SListNode<T>* NewElement = GetLast();

			NewElement->next = new SListNode<T>();
			NewElement = NewElement->next;
			NewElement->value = val;
			NewElement->next = nullptr;
			++_Size;
		}
		else
		{
			_Root = new SListNode();
			_Root->value = val;
			_Root->next = nullptr;
			++_Size;
		}
	};

	void push_back(value_type&& val) 
	{
		if (_Size > 0)
		{
			SListNode<T>* NewElement = GetLast();

			NewElement->next = new SListNode<T>();
			NewElement = NewElement->next;
			std::swap(NewElement->value, val);
			NewElement->next = nullptr;
			++_Size;
		}
		else
		{
			_Root = new SListNode();
			_Root->value = val;
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

	const_iterator cbegin() 
	{ 
		return const_iterator(_Root); 
	};

	const_iterator cend() 
	{ 
		return const_iterator(nullptr); 
	};

	reverse_iterator rbegin()
	{
		return reverse_iterator(_Root);
	};

	const_reverse_iterator rend()
	{
		return const_reverse_iterator(nullptr);
	};

protected:

	SListNode<T>* GetLast() 
	{
		SListNode<T>* Element = _Root;
		for (size_t i = 0; i < _Size; ++i)
		{
			Element = Element->next;
		}
		return Element;
	}

private:

	SListNode<T>* _Root;
	size_t _Size;

};



} // namespace slist