#pragma once

#include <iterator>
#include <vector>

namespace list {


template<class T, unsigned int N>
class FixedSList
{
public:
	// Forward declaration
	class FixedSListIterator;
	class SListNode;

	typedef T value_type;
	typedef T& reference_type;
	typedef const T& const_reference_type;

	typedef FixedSListIterator iterator;
	typedef FixedSListIterator const_iterator;
	typedef std::reverse_iterator<FixedSListIterator> reverse_iterator;
	typedef std::reverse_iterator<FixedSListIterator> const_reverse_iterator;

	explicit FixedSList()
	{
		_Root = &_Data[0];
		_Size = 0;
	};

	explicit FixedSList(size_t n)//n should be minor of N
	{
		value_type val = {};
		FixedSList(n, val);
	};

	FixedSList(size_t n, const value_type& val)//n should be minor of N
	{
		_Size = n;
		if (n > 0)
		{
			_Data[0].value = val;
			_Data[0].next = nullptr;
			_Root = &_Data[0];
		}
		for (size_t i = 1; i < n; ++i)
		{
			_Data[i - 1].next = &_Data[i];
			_Data[i].value = val;
			_Data[i].next = nullptr;
		}
	};

	FixedSList(FixedSListIterator first, FixedSListIterator last)//last - first should be minor of N
	{
		if (first != last)
		{
			_Data[0].value = *first;
			_Data[0].next = nullptr;
			_Root = &_Data[0];
			_Size = 1;
			first++;
		}
		for (; first != last; ++first, ++_Size)
		{
			_Data[_Size - 1].next = &_Data[_Size];
			_Data[_Size].value = *first;
			_Data[_Size].next = nullptr;
		}
	};

	FixedSList(const FixedSList& x)
	{
		_Size = x._Size;
		FixedSListIterator it = x.begin();
		size_t rootIndex = x._Root - &_Data[0];
		if (_Size > 0)
		{
			_Data[rootIndex].value = x._Data[0];
			_Data[rootIndex].next = nullptr;
			_Root = &_Data[rootIndex];
			++rootIndex;
		}
		for (rootIndex; rootIndex < x._Size; ++rootIndex, ++it)
		{
			_Data[rootIndex - 1].next = &_Data[rootIndex];
			_Data[rootIndex].value = x._Data[rootIndex];
			_Data[rootIndex].next = nullptr;
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
			_Data[0].value = *it;
			_Data[0].next = nullptr;
			_Root = &_Data[0];
			++it;
		}
		for (size_t i = 1; it != il.end(); ++it, ++i)
		{
			_Data[i - 1].next = &_Data[i - 1];
			_Data[i].value = *it;
			_Data[i].next = nullptr;
		}
	};

	virtual ~FixedSList()
	{
		for (size_t i=0;i<_Size;++i)
		{
			_Data[i].value.~value_type();
		}
		_Data = nullptr;
		_Size = 0;
		_Root = nullptr;
	};

	FixedSList& operator= (const FixedSList& x)
	{
		for (size_t i = 0; i < _Size; ++i)
		{
			_Data[i].value.~value_type();
		}
		_Data = nullptr;
		_Size = 0;
		_Root = nullptr;

		FixedSList aux(x);
		std::swap(_Root, aux._Root);
		std::swap(_Size, aux._Size);
		std::swap(_Data, aux._Data);
		return *this;
	};

	FixedSList& operator= (FixedSList&& x)
	{
		for (size_t i = 0; i < _Size; ++i)
		{
			_Data[i].value.~value_type();
		}
		_Data = nullptr;
		_Size = 0;
		_Root = nullptr;

		std::swap(_Root, x);
		std::swap(_Size, x);
		std::swap(_Data, x._Data);
		return *this;
	};

	FixedSList& operator= (std::initializer_list<value_type> il)
	{
		for (size_t i = 0; i < _Size; ++i)
		{
			_Data[i].value.~value_type();
		}
		_Data = nullptr;
		_Size = 0;
		_Root = nullptr;

		FixedSList aux(il);
		std::swap(_Root, aux._Root);
		std::swap(_Size, aux._Size);
		std::swap(_Data, aux._Data);
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
		if (_Root != &_Data[0])
		{

			SListNode* oldRoot = _Root;
			--_Root;
			_Root.value = val;
			_Root.next = oldRoot;
		}
		else
		{
			for (size_t i = _Size; i > 0; --i)
			{
				_Data[i + 1] = _Data[i];
			}
			_Data[0].value = val;
			++_Size;
			if (_Size > 1)
			{
				_Data[0].next = &_Data[1];
			}
			else
			{
				_Data[0].next = nullptr;
			}
			_Root = &_Data[0];
		}
	};

	void push_front(value_type&& val)
	{
		if (_Root != &_Data[0])
		{

			SListNode* oldRoot = _Root;
			--_Root;
			std::swap(_Root[0].value, val);
			_Root.next = oldRoot;
		}
		else
		{
			for (size_t i = _Size; i > 0; --i)
			{
				_Data[i + 1] = _Data[i];
			}
			std::swap(_Data[0].value , val);
			++_Size;
			if (_Size > 1)
			{
				_Data[0].next = &_Data[1];
			}
			else
			{
				_Data[0].next = nullptr;
			}
			_Root = &_Data[0];
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
		_Data[_Size]={ val,nullptr };
		++_Size;
		if (_Size > 1)
		{
			_Data[_Size - 2].next = _Data[_Size - 1];
		}
	};

	void push_back(value_type&& val)
	{
		SListNode newNode{ val,nullptr };
		//std::swap(newNode.val, val);
		_Data[_Size] = newNode;
		++_Size;
		if (_Size > 1)
		{
			_Data[_Size - 2].next = _Data[_Size - 1];
		}
	};

	iterator begin() { return iterator(&_Root); };
	iterator end() { return iterator(&_Root); };
	const_iterator cbegin() { return const_iterator(&_Root); };
	const_iterator cend() { return const_iterator(&_Root); };

private:

	SListNode* _Root;
	SListNode _Data[N];
	size_t _Size;

};


} // namespace list 

