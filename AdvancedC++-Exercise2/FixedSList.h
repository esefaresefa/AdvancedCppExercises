#pragma once

#include <iterator>
#include <vector>

namespace fixedslist {


template<class T, unsigned int N>
class FixedSList
{
public:
	// Forward declaration
	class FixedSListIterator;
	class FixedSListNode;

	typedef T value_type;
	typedef T& reference_type;
	typedef const T& const_reference_type;

	typedef FixedSListIterator iterator;
	typedef FixedSListIterator const_iterator;
	typedef std::reverse_iterator<FixedSListIterator> reverse_iterator;
	typedef std::reverse_iterator<FixedSListIterator> const_reverse_iterator;

	explicit FixedSList()
	{
		_Root = &m_data[0];
		_Size = 0;
	};

	explicit FixedSList(size_t n)//n should be minor of N
	{
		value_type val = {};
		SListArray aux(n, val);
		std::swap(m_data, aux.m_data);
		std::swap(_Root, aux._Root);
		std::swap(_Size, aux._Size);
	};

	FixedSList(size_t n, const value_type& val)//n should be minor of N
	{
		_Size = n;
		if (n > 0)
		{
			m_data[0].value = val;
			m_data[0].next = nullptr;
			_Root = &m_data[0];
		}
		for (size_t i = 1; i < n; ++i)
		{
			m_data[i - 1].next = &m_data[i];
			m_data[i].value = val;
			m_data[i].next = nullptr;
		}
	};

	FixedSList(FixedSListIterator first, FixedSListIterator last)//last - first should be minor of N
	{
		if (first != last)
		{
			m_data[0].value = *first;
			m_data[0].next = nullptr;
			_Root = &m_data[0];
			_Size = 1;
			first++;
		}
		for (; first != last; ++first, ++_Size)
		{
			m_data[_Size - 1].next = &m_data[_Size];
			m_data[_Size].value = *first;
			m_data[_Size].next = nullptr;
		}
	};

	FixedSList(const FixedSList& x)
	{
		_Size = x._Size;
		const_iterator it = x.begin();
		size_t rootIndex = x._Root - &m_data[0];
		if (_Size > 0)
		{
			m_data[rootIndex].value = x.m_data[0];
			m_data[rootIndex].next = nullptr;
			_Root = &m_data[rootIndex];
			++rootIndex;
		}
		for (rootIndex; rootIndex < x._Size; ++rootIndex, ++it)
		{
			m_data[rootIndex - 1].next = &m_data[rootIndex];
			m_data[rootIndex].value = x.m_data[rootIndex];
			m_data[rootIndex].next = nullptr;
		}
	};

	FixedSList(FixedSList&& x)
	{
		_Root = x._Root;
		_Size = x._Size;
		m_data = x.m_data;
		x.m_data = nullptr;
		x._Root = nullptr;
		x._Size = 0;
	};

	FixedSList(std::initializer_list<value_type> il)
	{
		_Root = nullptr;
		const value_type* it = il.begin(); //equivalent of std::initializer_list<value_type>::iterator
		_Size = il.size();
		if (_Size > 0)
		{
			m_data[0].value = *it;
			m_data[0].next = nullptr;
			_Root = &m_data[0];
			++it;
		}
		for (size_t i = 1; it != il.end(); ++it, ++i)
		{
			m_data[i - 1].next = &m_data[i - 1];
			m_data[i].value = *it;
			m_data[i].next = nullptr;
		}
	};

	virtual ~FixedSList()
	{
		for (size_t i=0;i<_Size;++i)
		{
			m_data[i].value.~value_type();
		}
		m_data = nullptr;
		_Size = 0;
		_Root = nullptr;
	};

	FixedSList& operator= (const FixedSList& x)
	{
		for (size_t i = 0; i < _Size; ++i)
		{
			m_data[i].value.~value_type();
		}
		m_data = nullptr;
		_Size = 0;
		_Root = nullptr;

		FixedSList aux(x);
		std::swap(_Root, aux._Root);
		std::swap(_Size, aux._Size);
		std::swap(m_data, aux.m_data);
		return *this;
	};

	FixedSList& operator= (FixedSList&& x)
	{
		for (size_t i = 0; i < _Size; ++i)
		{
			m_data[i].value.~value_type();
		}
		m_data = nullptr;
		_Size = 0;
		_Root = nullptr;

		std::swap(_Root, x);
		std::swap(_Size, x);
		std::swap(m_data, x.m_data);
		return *this;
	};

	FixedSList& operator= (std::initializer_list<value_type> il)
	{
		for (size_t i = 0; i < _Size; ++i)
		{
			m_data[i].value.~value_type();
		}
		m_data = nullptr;
		_Size = 0;
		_Root = nullptr;

		FixedSList aux(il);
		std::swap(_Root, aux._Root);
		std::swap(_Size, aux._Size);
		std::swap(m_data, aux.m_data);
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
		if (_Root != &m_data[0])
		{

			FixedSListNode* oldRoot = _Root;
			--_Root;
			_Root.value = val;
			_Root.next = oldRoot;
		}
		else
		{
			for (size_t i = _Size; i > 0; --i)
			{
				m_data[i + 1] = m_data[i];
			}
			m_data[0].value = val;
			++_Size;
			if (_Size > 1)
			{
				m_data[0].next = &m_data[1];
			}
			else
			{
				m_data[0].next = nullptr;
			}
			_Root = &m_data[0];
		}
	};

	void push_front(value_type&& val)
	{
		if (_Root != &m_data[0])
		{

			FixedSListNode* oldRoot = _Root;
			--_Root;
			std::swap(_Root[0].value, val);
			_Root.next = oldRoot;
		}
		else
		{
			for (size_t i = _Size; i > 0; --i)
			{
				m_data[i + 1] = m_data[i];
			}
			std::swap(m_data[0].value , val);
			++_Size;
			if (_Size > 1)
			{
				m_data[0].next = &m_data[1];
			}
			else
			{
				m_data[0].next = nullptr;
			}
			_Root = &m_data[0];
		}
	};

	void pop_front()
	{
		_Root.value.~value_type();
		_Root= _Root.next;
		--_Size;
	};

	void push_back(const value_type& val)
	{
		m_data[_Size]={ val,nullptr };
		++_Size;
		if (_Size > 1)
		{
			m_data[_Size - 2].next = m_data[_Size - 1];
		}
	};

	void push_back(value_type&& val)
	{
		FixedSListNode newNode{ val,nullptr };
		//std::swap(newNode.val, val);
		m_data[_Size] = newNode;
		++_Size;
		if (_Size > 1)
		{
			m_data[_Size - 2].next = m_data[_Size - 1];
		}
	};

	iterator begin() { return iterator(&_Root); };
	iterator end() { return iterator(&_Root); };
	const_iterator cbegin() { return const_iterator(&_Root); };
	const_iterator cend() { return const_iterator(&_Root); };

	class FixedSListIterator;

	class FixedSListNode {
	public:
		T value;
		FixedSListNode* next;
	};

private:
	FixedSListNode* _Root;
	FixedSListNode m_data[N];
	size_t _Size;

};





////////////////////////////////// FixedSListIterator //////////////////////////////////
template<class T, unsigned int N>
class FixedSList<T,N >::FixedSListIterator {

public:

	FixedSListIterator();

	FixedSListIterator(const FixedSListNode* pNode);

	FixedSListIterator& operator= (FixedSListNode* pNode);

	// Prefix ++ overload 
	FixedSListIterator& operator++();

	// Postfix ++ overload 
	FixedSListIterator operator++(int);

	bool operator!=(const FixedSListIterator& iterator);

	T operator*();

private:
	const FixedSListNode* _CurrentNode;
};


template<class T, unsigned int N>
FixedSList<T,N>::FixedSListIterator::FixedSListIterator() : _CurrentNode(_Root)
{ }


template<class T, unsigned int N>
FixedSList<T, N>::FixedSListIterator::FixedSListIterator(const FixedSListNode* node) : _CurrentNode(node)
{ }


template<class T, unsigned int N>
typename FixedSList<T, N>::FixedSListIterator& FixedSList<T, N>::FixedSListIterator::operator= (FixedSListNode* node)
{
	this->_CurrentNode = node;
	return *this;
}


template<class T, unsigned int N>
typename FixedSList<T, N>::FixedSListIterator& FixedSList<T, N>::FixedSListIterator::operator++ ()
{
	if (_CurrentNode)
		_CurrentNode = _CurrentNode->next;
	return *this;
}

template<class T, unsigned int N>
typename FixedSList<T, N>::FixedSListIterator FixedSList<T, N>::FixedSListIterator::operator++ (int)
{
	FixedSListIterator iterator = *this;
	++*this;
	return iterator;
}


template<class T, unsigned int N>
bool FixedSList<T, N>::FixedSListIterator::operator!= (const FixedSList<T, N>::FixedSListIterator& iterator)
{
	return _CurrentNode != iterator._CurrentNode;
}

template<class T, unsigned int N>
T FixedSList<T, N>::FixedSListIterator::operator* ()
{
	return _CurrentNode->value;
}

};

