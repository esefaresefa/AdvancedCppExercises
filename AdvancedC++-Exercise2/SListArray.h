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
		if (n > 0)
		{
			m_data[0].value=val;
			m_data[0].next = nullptr;
			_Root = &m_data[0];
		}
		for (size_t i=1; i < n; ++i)
		{
			m_data[i-1].next = &m_data[i];
			m_data[i].value = val;
			m_data[i].next = nullptr;
		}
	};

	SListArray(SListArrayIterator first, SListArrayIterator last)
	{
		m_data = new std::vector<SListArrayNode>(last - first);
		if (first != last)
		{
			m_data[0].value = *first;
			m_data[0].next = nullptr;
			_Root = &m_data[0];
			_Size = 1;
			first++;
		}
		for (; first != last; ++first,++_Size)
		{
			m_data[_Size-1].next = &m_data[_Size];
			m_data[_Size].value = *first;
			m_data[_Size].next = nullptr;
		}
	};

	SListArray(const SListArray& x)
	{
		_Root = x._Root;
		_Size = x._Size;
		m_data = new std::vector<SListArrayNode>(_Size);
		SListArrayIterator it = x.begin();
		if (_Size > 0)
		{
			m_data[0].value = x.m_data[0];
			m_data[0].next = nullptr;
		}
		for (int i = 1; i < x._Size; ++i, ++it)
		{
			m_data[i - 1].next = &m_data[i];
			m_data[i].value = x.m_data[i];
			m_data[i].next = nullptr;
		}
	};

	SListArray(SListArray&& x)
	{
		_Root = x._Root;
		_Size = x._Size;
		m_data = x.m_data;
		x.m_data = new std::vector<SListArrayNode>();
		x._Root = nullptr;
		x._Size = 0;
	};

	SListArray(std::initializer_list<value_type> il)
	{
		_Root = nullptr;
		const value_type* it = il.begin(); //equivalent of std::initializer_list<value_type>::iterator
		_Size = il.size();
		m_data = new std::vector<SListArrayNode>(il.size());
		if (_Size > 0)
		{
			m_data[0].value = *it;
			m_data[0].next = nullptr;
			_Root = &m_data[0]; 
			++it;
		}
		for (size_t i=1; it != il.end(); ++it,++i)
		{
			m_data[i-1].next = &m_data[i - 1];
			m_data[i].value = *it;
			m_data[i].next = nullptr;
		}
	};

	virtual ~SListArray()
	{
		_Size = 0;
		_Root = nullptr;
		delete[] m_data;
	};

	SListArray& operator= (const SListArray& x)
	{
		_Size = 0;
		_Root = nullptr;
		delete[] m_data;

		this = SList(x);
	};

	SListArray& operator= (SListArray&& x)
	{
		_Size = 0;
		_Root = nullptr;
		delete[] m_data;

		this = SList(std::move(x));
	};

	SListArray& operator= (std::initializer_list<value_type> il)
	{
		_Size = 0;
		_Root = nullptr;
		delete[] m_data;

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
		m_data.insert(0, { val,_Root });
		_Root = &m_data[0];
		++_Size;
	};

	void push_front(value_type&& val)
	{
		SListArrayNode newNode{ val,_Root };
		//std::swap(newNode.val, val);
		m_data.insert(0, newNode);
		_Root = &m_data[0];
		++_Size;
	};

	void pop_front()
	{
		if (_Size > 0)
		{
			m_data[0].value.~value_type();
			m_data.erase(m_data.begin());
			_Root = &m_data[0];
			--_Size;
		}
	};

	void push_back(const value_type& val)
	{
		m_data.push_back({ val,nullptr });
		++_Size;
		if (_Size > 1)
		{
			m_data[_Size - 2].next = m_data[_Size - 1];
		}
	};

	void push_back(value_type&& val)
	{
		SListArrayNode newNode{ val,nullptr };
		//std::swap(newNode.val, val);
		m_data.push_back({ newNode });
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

