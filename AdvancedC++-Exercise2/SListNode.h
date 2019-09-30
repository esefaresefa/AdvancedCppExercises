#pragma once


namespace slist {


template<typename T>
class SListNode {

public:

	typedef T value_type;
	typedef T& reference_type;
	typedef const T& const_reference_type;

	T value;
	SListNode* next;
};


} // namespace slist