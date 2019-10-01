#pragma once

#include "SListIterator.h"
#include "ListNode.h"
#include <iterator>


namespace list {

	   	  
template<typename T>
class SList
{

public:

	typedef T value_type;
	typedef T& reference_type;
	typedef const T& const_reference_type;

	typedef SListIterator<ListNode<T>> iterator;
	typedef SListIterator<const ListNode<T>> const_iterator;
	typedef std::reverse_iterator<SListIterator<T>> reverse_iterator;
	typedef std::reverse_iterator<const SListIterator<T>> const_reverse_iterator;
	
	SList();

	explicit SList(size_t n);

	SList(size_t n, const value_type& val);

	SList(iterator first, iterator last);

	SList(const SList& x);

	SList(SList&& x);

	SList(std::initializer_list<value_type> il);

	virtual ~SList();

	SList& operator= (const SList& x);

	SList& operator= (SList&& x);

	SList& operator= (std::initializer_list<value_type> il);

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

protected:

	ListNode<T>* GetLast();

private:

	ListNode<T>* _Root;

	size_t _Size;
};


} // namespace list

#include "SList.inl"