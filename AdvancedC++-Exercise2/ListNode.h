#pragma once


namespace list {


template<typename T>
class ListNode {

public:

	typedef T value_type;
	typedef T& reference_type;
	typedef const T& const_reference_type;

	T value;
	ListNode* next;
};


} // namespace list