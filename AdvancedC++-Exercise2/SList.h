#pragma once

#include <iterator>

namespace slist {


template<class T>
class SList
{

public:
	// Forward declaration
	class SListIterator;
	class SlistNode;
	
	typedef T value_type;
	typedef T& reference_type;
	typedef const T& const_reference_type;

	typedef SListIterator iterator;
	typedef SListIterator const_iterator;
	typedef std::reverse_iterator<SListIterator> reverse_iterator;
	typedef std::reverse_iterator<SListIterator> const_reverse_iterator;
	
	SList() {};
	virtual ~SList() {};
	iterator begin() { return iterator(&_Root); };
	iterator end() { return iterator(&_Root); };
	const_iterator cbegin() { return const_iterator(&_Root); };
	const_iterator cend() { return const_iterator(&_Root); };

	class SListIterator;

	class SlistNode {
	public:
		T value;
		SlistNode* next;
	};

private:
	SlistNode* _Root;

	size_t _Size;

};




////////////////////////////////// SListIterator //////////////////////////////////
template<class T>
class SList<T>::SListIterator {
	
public:

	SListIterator();

	SListIterator(const SlistNode* pNode);

	SListIterator& operator= (SlistNode* pNode);

	// Prefix ++ overload 
	SListIterator& operator++();

	// Postfix ++ overload 
	SListIterator operator++(int);

	bool operator!=(const SListIterator& iterator);

	T operator*();

private:
	const SlistNode* _CurrentNode;
};


template<class T>
SList<T>::SListIterator::SListIterator() : _CurrentNode(_Root)
{ }


template<class T>
SList<T>::SListIterator::SListIterator(const SlistNode* node) : _CurrentNode(node)
{ }


template<class T>
typename SList<T>::SListIterator& SList<T>::SListIterator::operator= (SlistNode* node)
{
	this->_CurrentNode = node;
	return *this;
}


template<class T>
typename SList<T>::SListIterator& SList<T>::SListIterator::operator++ ()
{
	if (_CurrentNode)
		_CurrentNode = _CurrentNode->next;
	return *this;
}


template<class T>
typename SList<T>::SListIterator SList<T>::SListIterator::operator++ (int)
{
	SListIterator iterator = *this;
	++*this;
	return iterator;
}


template<class T>
bool SList<T>::SListIterator::operator!= (const SList<T>::SListIterator& iterator)
{
	return _CurrentNode != iterator._CurrentNode;
}


template<class T>
T SList<T>::SListIterator::operator* ()
{
	return _CurrentNode->value;
}



} // namespace slist