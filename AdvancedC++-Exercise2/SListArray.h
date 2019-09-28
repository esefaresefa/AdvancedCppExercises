#pragma once

#include <iterator>
#include <vector>

namespace slistarray {


	template<class T>
class SListArray
{
public:
	// Forward declaration
	class SListArrayIterator;
	class SListArrayNode;

	typedef T value_type;
	typedef T& reference_type;
	typedef const T& const_reference_type;

	typedef SListArrayIterator iterator;
	typedef SListArrayIterator const_iterator;
	typedef std::reverse_iterator<SListArrayIterator> reverse_iterator;
	typedef std::reverse_iterator<SListArrayIterator> const_reverse_iterator;

	explicit SListArray()
	{
		m_data = new std::vector<SListArrayNode>();
		_Root = nullptr;
		_Size = 0;
	};

	explicit SListArray(size_t n)
	{
		value_type val = {};
		SList(n, val);
	};

	SListArray(size_t n, const value_type& val)
	{
		m_data = new std::vector<SListArrayNode>(n);
		_Size = n;
		SListArrayNode* AuxNode = nullptr;
		for (; n > 0; --n)
		{
			if (n == _Size)
			{
				_Root = new SListArrayNode();
				_Root->value = val;
				_Root->next = AuxNode;
			}
			else
			{
				AuxNode = new SListArrayNode();
				AuxNode->value = val;
				AuxNode->Next = nullptr;
				AuxNode = AuxNode->next;
			}
		}
	};

	SListArray(SListArrayIterator first, SListArrayIterator last)
	{
		_Root = new SListArrayNode();
		_Root->value = *first;
		_Root->next = nullptr;
		_Size = 0;
		SListArrayNode* AuxNode = _Root->next;
		first++;
		for (; first != last; ++first)
		{
			AuxNode = new SListArrayNode();
			AuxNode->value = *first;
			AuxNode->Next = nullptr;
			AuxNode = AuxNode->next;
			++_Size;
		}
	};

	SListArray(const SListArray& x)
	{
		_Root = nullptr;
		SListArrayNode* AuxNode = _Root;
		SListArrayIterator it = x.begin();
		_Size = 0;
		for (int i = 0; i < x._Size; ++i, ++it)
		{
			if (i == 0)
			{
				_Root = new SListArrayNode();
				_Root->value = *it;
				_Root->next = nullptr;
				AuxNode = _Root->next;
			}
			else
			{
				AuxNode = new SListArrayNode();
				AuxNode->value = *it;
				AuxNode->Next = nullptr;
				AuxNode = AuxNode->next;
			}
			++_Size;
		}
	};

	SListArray(SListArray&& x)
	{
		_Root = x._Root;
		_Size = x._Size;
		x._Root = nullptr;
		x._Size = 0;
	};

	SListArray(std::initializer_list<value_type> il)
	{
		_Root = nullptr;
		SListArrayNode* AuxNode = _Root;
		const value_type* it; //equivalent of std::initializer_list<value_type>::iterator
		_Size = 0;
		for (it = il.begin(); it != il.end(); ++it)
		{
			if (it == il.begin())
			{
				_Root = new SListArrayNode();
				_Root->value = *it;
				_Root->next = nullptr;
				AuxNode = _Root->next;
			}
			else
			{
				AuxNode = new SListArrayNode();
				AuxNode->value = *it;
				AuxNode->Next = nullptr;
				AuxNode = AuxNode->next;
			}
			++_Size;
		};
	};

	virtual ~SListArray()
	{
		SListArrayNode* AuxNode = nullptr;
		for (; _Size > 0; _Size--)
		{
			AuxNode = _Root;
			_Root = _Root->next;
			AuxNode->value.~value_type();
			delete AuxNode;
		}
		delete _Root;
	};

	SListArray& operator= (const SListArray& x)
	{
		SListArrayNode* AuxNode = nullptr;
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

	SListArray& operator= (SListArray&& x)
	{
		SListArrayNode* AuxNode = nullptr;
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

	SListArray& operator= (std::initializer_list<value_type> il)
	{
		SListArrayNode* AuxNode = nullptr;
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
		SListArrayNode* NewElement = new SListArrayNode();
		NewElement->value = val;
		NewElement->next = _Root;
		_Root = NewElement;
		++_Size;
	};

	void push_front(value_type&& val)
	{
		SListArrayNode* NewElement = new SListArrayNode();
		std::swap(NewElement->value, val);
		NewElement->next = _Root;
		_Root = NewElement;
		++_Size;
	};

	void pop_front()
	{
		SListArrayNode* AuxNode = _Root;
		_Root = _Root->next;
		--_Size;
		AuxNode->value.~value_type();
		delete AuxNode;
	};

	void push_back(const value_type& val)
	{
		SListArrayNode* NewElement = _Root;

		for (size_t i = 0; i < _Size; ++i)
		{
			NewElement = NewElement->next;
		}

		NewElement->next = new SListArrayNode();
		NewElement = NewElement->next;
		NewElement->value = val;
		NewElement->next = nullptr;
		++_Size;
	};

	void push_back(value_type&& val)
	{
		SListArrayNode* NewElement = _Root;

		for (size_t i = 0; i < _Size; ++i)
		{
			NewElement = NewElement->next;
		}

		NewElement->next = new SListArrayNode();
		NewElement = NewElement->next;
		std::swap(NewElement->value, val);
		NewElement->next = nullptr;
		++_Size;
	};

	iterator begin() { return iterator(&_Root); };
	iterator end() { return iterator(&_Root); };
	const_iterator cbegin() { return const_iterator(&_Root); };
	const_iterator cend() { return const_iterator(&_Root); };

	class SListArrayIterator;

	class SListArrayNode {
	public:
		T value;
		SListArrayNode* next;
	};

private:
	SListArrayNode* _Root;
	std::vector <SListArrayNode> m_data;
	size_t _Size;

};




////////////////////////////////// SListArrayIterator //////////////////////////////////
template<class T>
class SListArray<T>::SListArrayIterator {

public:

	SListArrayIterator();

	SListArrayIterator(const SListArrayNode* pNode);

	SListArrayIterator& operator= (SListArrayNode* pNode);

	// Prefix ++ overload 
	SListArrayIterator& operator++();

	// Postfix ++ overload 
	SListArrayIterator operator++(int);

	bool operator!=(const SListArrayIterator& iterator);

	T operator*();

private:
	const SListArrayNode* _CurrentNode;
};


template<class T>
SListArray<T>::SListArrayIterator::SListArrayIterator() : _CurrentNode(_Root)
{ }


template<class T>
SListArray<T>::SListArrayIterator::SListArrayIterator(const SListArrayNode* node) : _CurrentNode(node)
{ }


template<class T>
typename SListArray<T>::SListArrayIterator& SListArray<T>::SListArrayIterator::operator= (SListArrayNode* node)
{
	this->_CurrentNode = node;
	return *this;
}


template<class T>
typename SListArray<T>::SListArrayIterator& SListArray<T>::SListArrayIterator::operator++ ()
{
	if (_CurrentNode)
		_CurrentNode = _CurrentNode->next;
	return *this;
}


template<class T>
typename SListArray<T>::SListArrayIterator SListArray<T>::SListArrayIterator::operator++ (int)
{
	SListArrayIterator iterator = *this;
	++*this;
	return iterator;
}


template<class T>
bool SListArray<T>::SListArrayIterator::operator!= (const SListArray<T>::SListArrayIterator& iterator)
{
	return _CurrentNode != iterator._CurrentNode;
}


template<class T>
T SListArray<T>::SListArrayIterator::operator* ()
{
	return _CurrentNode->value;
}



} // namespace slist

