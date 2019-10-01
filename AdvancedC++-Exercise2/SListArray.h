#pragma once

#include "ListNode.h"
#include "SListArrayIterator.h"
#include <iterator>
#include <vector>


namespace list {


template<class T>
class SListArray
{

public:

	typedef T value_type;
	typedef T& reference_type;
	typedef const T& const_reference_type;

	typedef SListArrayIterator<ListNode<T>> iterator;
	typedef SListArrayIterator<const ListNode<T>> const_iterator;
	typedef std::reverse_iterator<SListArrayIterator<T>> reverse_iterator;
	typedef std::reverse_iterator<const SListArrayIterator<T>> const_reverse_iterator;

	// Constructors

	SListArray();

	explicit SListArray(size_t n);

	SListArray(size_t n, const value_type& val);

	SListArray(iterator first, iterator last);

	SListArray(const SListArray& x);

	SListArray(SListArray&& x);

	SListArray(std::initializer_list<value_type> il);


	// Destructor
	virtual ~SListArray();


	// Copy operators
	SListArray& operator= (const SListArray& x);

	SListArray& operator= (SListArray&& x);

	SListArray& operator= (std::initializer_list<value_type> il);


	// Capacity
	bool empty() const;

	size_t size() const;


	// Member access
	ListNode<T>& front();

	ListNode<T>& back();


	// Modifiers
	void push_front(const value_type& val);

	void push_front(value_type&& val);

	void pop_front();

	void push_back(const value_type& val);

	void push_back(value_type&& val);

	void pop_back();

	iterator insert(iterator pos, const T& value);

	iterator erase(iterator pos);

	iterator erase(iterator first, iterator last);

	void resize(size_t count, const value_type & value);

	void resize(size_t count);

	void clear();

	// Iterators

	iterator begin();

	iterator end() ;

	const_iterator cbegin() const;

	const_iterator cend() const;

	reverse_iterator rbegin();

	reverse_iterator rend();

	const_reverse_iterator crbegin() const;

	const_reverse_iterator crend() const;

private:

	ListNode<T>* _Root;

	std::vector<ListNode<T>> _Data;

	size_t _Size;
};


} // namespace list

#include "SListArray.inl"