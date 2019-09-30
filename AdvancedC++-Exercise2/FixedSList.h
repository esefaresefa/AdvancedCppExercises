#pragma once

#include "FixedSListIterator.h"
#include <iterator>
#include <vector>
#include <stdexcept>

namespace list {


template<class T, unsigned int N>
class FixedSList
{

public:

	typedef T value_type;
	typedef T& reference_type;
	typedef const T& const_reference_type;

	typedef FixedSListIterator<T> iterator;
	typedef FixedSListIterator<T> const_iterator;
	typedef std::reverse_iterator<FixedSListIterator<T>> reverse_iterator;
	typedef std::reverse_iterator<FixedSListIterator<const T>> const_reverse_iterator;

	FixedSList()
	{
		_Root = &_Data[0];
		_Size = 0;
	};

	explicit FixedSList(size_t n)//n should be minor of N
	{
		value_type val = {};
		SListArray aux(n, val);
		std::swap(_Data, aux._Data);
		std::swap(_Root, aux._Root);
		std::swap(_Size, aux._Size);
	};

	FixedSList(size_t n, const value_type& val)//n should be minor of N
	{
		_Size = n;
		if (n > 0)
		{
			_Data[0] = val;
			_Root = &_Data[0];
		}
		for (size_t i = 1; i < n; ++i)
		{
			_Data[i] = val;
		}
	};

	FixedSList(iterator first, iterator last)//last - first should be minor of N
	{
		if (first != last)
		{
			_Data[0] = *first;
			_Root = &_Data[0];
			_Size = 1;
			first++;
		}
		for (; first != last; ++first, ++_Size)
		{
			_Data[_Size] = *first;
		}
	};

	FixedSList(const FixedSList& x)
	{
		_Size = x._Size;
		const_iterator it = x.begin();
		size_t rootIndex = x._Root - &_Data[0];
		if (_Size > 0)
		{
			_Data[rootIndex] = x._Data[0];
			_Root = &_Data[rootIndex];
			++rootIndex;
		}
		for (rootIndex; rootIndex < x._Size; ++rootIndex, ++it)
		{
			_Data[rootIndex] = x._Data[rootIndex];
		}
	};

	FixedSList(FixedSList&& x)
	{
		_Root = x._Root;
		_Size = x._Size;
		_Data = x._Data;
		x._Data = nullptr;
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
			_Data[0] = *it;
			_Root = &_Data[0];
			++it;
		}
		for (size_t i = 1; it != il.end(); ++it, ++i)
		{
			_Data[i] = *it;
		}
	};

	virtual ~FixedSList()
	{
		for (size_t i=0;i<_Size;++i)
		{
			_Data[i].~value_type();
		}

		_Size = 0;
		_Root = nullptr;
	};

	FixedSList& operator= (const FixedSList& x)
	{
		for (size_t i = 0; i < _Size; ++i)
		{
			_Data[i].~value_type();
		}

		_Size = 0;
		_Root = nullptr;

		FixedSList aux(x);
		std::swap(*this, aux);
		return *this;
	};

	FixedSList& operator= (FixedSList&& x)
	{
		for (size_t i = 0; i < _Size; ++i)
		{
			_Data[i].~value_type();
		}

		_Size = 0;
		_Root = nullptr;

		std::swap(*this, x);
		return *this;
	};

	FixedSList& operator= (std::initializer_list<value_type> il)
	{
		for (size_t i = 0; i < _Size; ++i)
		{
			_Data[i].~value_type();
		}

		_Size = 0;
		_Root = nullptr;

		FixedSList aux(il);
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
		if (_Root != &_Data[0])
		{

			T* oldRoot = _Root;
			--_Root;
			*_Root = val;
		}
		else
		{
			if (_Size < N)
			{
				for (size_t i = _Size; i > 0; --i)
				{
					_Data[i + 1] = _Data[i];
				}
				_Data[0] = val;
				++_Size;
				_Root = &_Data[0];
			}
			else
			{
				throw std::out_of_range("index out of fixed list");
			}
		}
	};

	void push_front(value_type&& val)
	{
		if (_Root != &_Data[0])
		{

			T* oldRoot = _Root;
			--_Root;
			std::swap(*_Root, val);
		}
		else
		{
			if (_Size < N)
			{
				for (size_t i = _Size; i > 0; --i)
				{
					_Data[i + 1] = _Data[i];
				}
				std::swap(_Data[0], val);
				++_Size;
				_Root = &_Data[0];
			}
			else
			{
				throw std::out_of_range("index out of fixed list");
			}
		}
	};

	void pop_front()
	{
		_Root.~value_type();
		--_Size;
	};

	void push_back(const value_type& val)
	{
		int forwardData=_Root - &_Data[0];
		if (forwardData + _Size < N)
		{
			_Data[_Size] = { val, nullptr };
			++_Size;
		}
		else
		{
			if (_Size < N)
			{
				iterator it = _Root;
				for (; it != end() ; ++it)
				{
					*it = *(it+1);
				}
				*it = val;
				++_Size;
			}
			else 
			{
				throw std::out_of_range("index out of fixed list");
			}
		}
	};

	void push_back(value_type&& val)
	{
		int forwardData = _Root - &_Data[0];
		if (forwardData + _Size < N)
		{
			_Data[_Size] = { val, nullptr };
			++_Size;
		}
		else
		{
			if (_Size < N)
			{
				iterator it = _Root;
				for (; it != end(); ++it)
				{
					*it = *(it + 1);
				}
				std::swap(*it = val);
				++_Size;
			}
			else
			{
				throw std::out_of_range("index out of fixed list");
			}
		}
	};

	iterator begin()
	{
		return iterator(&_Data[0]);
	};

	iterator end()
	{
		return iterator(_Data[_Size]);
	};

	const_iterator cbegin() const
	{
		return const_iterator(&_Data[0]);
	};

	const_iterator cend() const
	{
		return const_iterator(_Data[_Size]);
	};

	reverse_iterator rbegin()
	{
		return reverse_iterator(&_Data[0]);
	};

	const_reverse_iterator rend()
	{
		return const_reverse_iterator(_Data[_Size]);
	};


private:

	T* _Root;

	T _Data[N];

	size_t _Size;

};


} // namespace list 

