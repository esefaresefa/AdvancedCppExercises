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

	FixedSList();

	// n should be minor of N
	explicit FixedSList(size_t n);
	
	// n should be minor of N
	FixedSList(size_t n, const value_type& val);

	// last - first should be minor of N
	FixedSList(iterator first, iterator last);

	FixedSList(const FixedSList& x);

	FixedSList(FixedSList&& x);

	FixedSList(std::initializer_list<value_type> il);

	virtual ~FixedSList();

	FixedSList& operator= (const FixedSList& x);

	FixedSList& operator= (FixedSList&& x);

	FixedSList& operator= (std::initializer_list<value_type> il);

	bool empty() const;

	size_t size() const;

	void push_front(const value_type& val);

	void push_front(value_type&& val);

	void pop_front();

	void push_back(const value_type& val);

	void push_back(value_type&& val);

	iterator begin();

	iterator end();

	const_iterator cbegin() const;

	const_iterator cend() const;

	reverse_iterator rbegin();

	reverse_iterator rend();

	const_reverse_iterator crbegin() const;

	const_reverse_iterator crend() const;


private:

	T* _Root;

	T _Data[N];

	size_t _Size;
};


} // namespace list 

#include "FixedSList.inl"

