#pragma once

#include <iterator>

namespace slist {


template<class T>
class SList
{

public:
	// Forward declaration
	class SListIterator;
	class SlistNode;
	
	typedef T value_type;
	typedef T& reference_type;
	typedef const T& const_reference_type;

	typedef SListIterator iterator;
	typedef SListIterator const_iterator;
	typedef std::reverse_iterator<SListIterator> reverse_iterator;
	typedef std::reverse_iterator<SListIterator> const_reverse_iterator;
	
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
		SlistNode* AuxNode = nullptr;
		_Size = n;
		if (n > 0)
		{
			_Root = new SlistNode();
			_Root->value = val;
			_Root->next = nullptr;
			AuxNode = _Root;
			--n;
		}
		for (; n > 0; --n)
		{
			AuxNode->next = new SlistNode();
			AuxNode = AuxNode->next;
			AuxNode->value = val;
		}
		AuxNode->next = nullptr;
	};

	SList(SListIterator first, SListIterator last)
	{
		_Root = new SlistNode();
		_Root->value = *first;
		_Root->next = nullptr;
		_Size = 1;
		SlistNode* AuxNode = _Root;
		first++;
		for (;first!=last;++first)
		{
			AuxNode->next = new SlistNode();
			AuxNode = AuxNode->next;
			AuxNode->value = *first;
			++_Size;
		}
		AuxNode->next = nullptr;
	};

	SList(const SList& x)
	{
		_Root = nullptr;
		SlistNode* AuxNode = _Root;
		SListIterator it = x.begin();
		_Size = x._Size;
		if (_Size > 0)
		{
			_Root = new SlistNode();
			_Root->value = *it;
			_Root->next = nullptr;
			AuxNode = _Root;
		}
		for (int i=1; i < x._Size; ++i, ++it)
		{
			AuxNode->next = new SlistNode();
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
		SlistNode* AuxNode = _Root;
		const value_type* it = il.begin(); //equivalent of std::initializer_list<value_type>::iterator
		_Size = il.size();
		if (il.size()>0)
		{
			_Root = new SlistNode();
			_Root->value = *it;
			_Root->next = nullptr;
			AuxNode = _Root; 
			++it;
		}
		for (; it != il.end(); ++it)
		{
			AuxNode->next = new SlistNode();
			AuxNode = AuxNode->next;
			AuxNode->value = *it;
		}
		AuxNode->next = nullptr;
	};

	virtual ~SList() 
	{
		SlistNode* AuxNode = nullptr;
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
		SlistNode* AuxNode = nullptr;
		for (; _Size > 0; _Size--)
		{
			AuxNode = _Root;
			_Root = _Root->next;
			AuxNode->value.~value_type();
			delete AuxNode;
		}
		delete _Root;
		this = SList(x);
	};

	SList& operator= (SList&& x) 
	{
		SlistNode* AuxNode=nullptr;
		for (; _Size > 0; _Size--)
		{
			AuxNode = _Root;
			_Root = _Root->next;
			AuxNode->value.~value_type();
			delete AuxNode;
		}
		delete _Root;
		this = SList(std::move(x));
	};

	SList& operator= (std::initializer_list<value_type> il)
	{
		SlistNode* AuxNode = nullptr;
		for (; _Size > 0; _Size--)
		{
			AuxNode = _Root;
			_Root = _Root->next;
			AuxNode->value.~value_type();
			delete AuxNode;
		}
		delete _Root;
		this = SList(il);
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
		SlistNode* NewElement = new SlistNode();
		NewElement->value = val;
		NewElement->next = _Root;
		_Root = NewElement;
		++_Size;
	};

	void push_front(value_type&& val) 
	{
		SlistNode* NewElement = new SlistNode();
		std::swap(NewElement->value, val);
		NewElement->next = _Root;
		_Root = NewElement;
		++_Size;
	};

	void pop_front() 
	{
		if (_Size > 0)
		{
			SlistNode* AuxNode = _Root;
			_Root = _Root->next;
			--_Size;
			AuxNode->value.~value_type();
			delete AuxNode;
		}
	};

	void push_back(const value_type& val)
	{
		SlistNode* NewElement = _Root;

		for (size_t i = 0; i < _Size; ++i)
		{
			NewElement = NewElement->next;
		}

		NewElement->next = new SlistNode();
		NewElement = NewElement->next;
		NewElement->value = val;
		NewElement->next = nullptr;
		++_Size;
	};

	void push_back(value_type&& val) 
	{
		SlistNode* NewElement = _Root;

		for (size_t i = 0; i < _Size; ++i)
		{
			NewElement = NewElement->next;
		}

		NewElement->next = new SlistNode();
		NewElement = NewElement->next;
		std::swap(NewElement->value,val);
		NewElement->next = nullptr;
		++_Size;
	};

	iterator begin() { return iterator(&_Root); };
	iterator end() { return iterator(&_Root); };
	const_iterator cbegin() { return const_iterator(&_Root); };
	const_iterator cend() { return const_iterator(&_Root); };

	class SListIterator;

	class SlistNode {
	public:
		T value;
		SlistNode* next;
	};

private:
	SlistNode* _Root;
	size_t _Size;

};




////////////////////////////////// SListIterator //////////////////////////////////
template<class T>
class SList<T>::SListIterator {
	
public:

	SListIterator();

	SListIterator(const SlistNode* pNode);

	SListIterator& operator= (SlistNode* pNode);

	// Prefix ++ overload 
	SListIterator& operator++();

	// Postfix ++ overload 
	SListIterator operator++(int);

	bool operator!=(const SListIterator& iterator);

	T operator*();

private:
	const SlistNode* _CurrentNode;
};


template<class T>
SList<T>::SListIterator::SListIterator() : _CurrentNode(_Root)
{ }


template<class T>
SList<T>::SListIterator::SListIterator(const SlistNode* node) : _CurrentNode(node)
{ }


template<class T>
typename SList<T>::SListIterator& SList<T>::SListIterator::operator= (SlistNode* node)
{
	this->_CurrentNode = node;
	return *this;
}


template<class T>
typename SList<T>::SListIterator& SList<T>::SListIterator::operator++ ()
{
	if (_CurrentNode)
		_CurrentNode = _CurrentNode->next;
	return *this;
}


template<class T>
typename SList<T>::SListIterator SList<T>::SListIterator::operator++ (int)
{
	SListIterator iterator = *this;
	++*this;
	return iterator;
}


template<class T>
bool SList<T>::SListIterator::operator!= (const SList<T>::SListIterator& iterator)
{
	return _CurrentNode != iterator._CurrentNode;
}


template<class T>
T SList<T>::SListIterator::operator* ()
{
	return _CurrentNode->value;
}



} // namespace slist