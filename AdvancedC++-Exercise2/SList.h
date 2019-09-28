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
		SlistNode* AuxNode = _Root;
		_Size = n;
		for (; n > 0; --n)
		{
			if (n == _Size)
			{
				_Root = new SlistNode();
				_Root->value = val;
				_Root->next = nullptr;
				AuxNode = _Root->next;
			}
			else
			{
				AuxNode = new SlistNode();
				AuxNode->value = val;
				AuxNode->Next = nullptr;
				AuxNode = AuxNode->next;
			}
		}
	};

	SList(SListIterator first, SListIterator last)
	{
		_Root = new SlistNode();
		_Root->value = *first;
		_Root->next = nullptr;
		_Size = 0;
		SlistNode* AuxNode = _Root->next;
		first++;
		for (;first!=last;++first)
		{
			AuxNode= new SlistNode();
			AuxNode->value = *first;
			AuxNode->Next = nullptr;
			AuxNode = AuxNode->next;
			++_Size;
		}
	};

	SList(const SList& x)
	{
		_Root = nullptr;
		SlistNode* AuxNode = _Root;
		SListIterator it = x.begin();
		_Size = 0;
		for (int i=0; i < x._Size; ++i, ++it)
		{
			if (i == 0) 
			{
				_Root = new SlistNode();
				_Root->value = *it;
				_Root->next = nullptr;
				AuxNode = _Root->next;
			}
			else
			{
				AuxNode = new SlistNode();
				AuxNode->value = *it;
				AuxNode->Next = nullptr;
				AuxNode = AuxNode->next;
			}
			++_Size;
		}
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
		const value_type* it; //equivalent of std::initializer_list<value_type>::iterator
		_Size = 0;
		for (it = il.begin(); it != il.end(); ++it)
		{
			if (it == il.begin())
			{
				_Root = new SlistNode();
				_Root->value = *it;
				_Root->next = nullptr;
				AuxNode = _Root->next;
			}
			else
			{
				AuxNode = new SlistNode();
				AuxNode->value = *it;
				AuxNode->Next = nullptr;
				AuxNode = AuxNode->next;
			}
			++_Size;
		};
	};

	virtual ~SList() 
	{
		for (; _Size > 0; _Size--)
		{
			SlistNode* AuxNode = _Root;
			_Root = _Root->next;
			AuxNode->value.~value_type();
			AuxNode->next = nullptr;
			AuxNode = nullptr;
		}
		_Root = nullptr;
	};

	SList& operator= (const SList& x)
	{
		for (; _Size > 0; _Size--)
		{
			SlistNode* AuxNode = _Root;
			_Root = _Root->next;
			AuxNode->value.~value_type();
			AuxNode->next = nullptr;
			AuxNode = nullptr;
		}
		_Root = nullptr;
		this = SList(x);
	};

	SList& operator= (SList&& x) 
	{
		for (; _Size > 0; _Size--)
		{
			SlistNode* AuxNode = _Root;
			_Root = _Root->next;
			AuxNode->value.~value_type();
			AuxNode->next = nullptr;
			AuxNode = nullptr;
		}
		_Root = nullptr;
		this = SList(std::move(x));
	};

	SList& operator= (std::initializer_list<value_type> il)
	{
		for (; _Size > 0; _Size--)
		{
			SlistNode* AuxNode = _Root;
			_Root = _Root->next;
			AuxNode->value.~value_type();
			AuxNode->next = nullptr;
			AuxNode = nullptr;
		}
		_Root = nullptr;
		this = SList(il);
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