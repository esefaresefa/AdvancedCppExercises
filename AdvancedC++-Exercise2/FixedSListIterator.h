#pragma once


namespace list {


template<typename U>
class FixedSListIterator {

public:

	FixedSListIterator();

	FixedSListIterator(typename U* pNode);

	FixedSListIterator& operator= (U* pNode);

	// Prefix ++ overload 
	FixedSListIterator& operator++();

	// Postfix ++ overload 
	FixedSListIterator operator++(int);

	bool operator!=(const FixedSListIterator& iterator);

	typename U::value_type operator*();

private:

	U* _CurrentNode;
};



template<typename U>
FixedSListIterator<U>::FixedSListIterator() : _CurrentNode(nullptr)
{ }



template<typename U>
FixedSListIterator<U>::FixedSListIterator(U* node) : _CurrentNode(node)
{ }


template<typename U>
FixedSListIterator<U>& FixedSListIterator<U>::operator= (U* node)
{
	this->_CurrentNode = node;
	return *this;
}


template<typename U>
FixedSListIterator<U>& FixedSListIterator<U>::operator++ ()
{
	if (_CurrentNode)
		_CurrentNode = _CurrentNode->next;
	return *this;
}


template<typename U>
FixedSListIterator<U> FixedSListIterator<U>::operator++ (int)
{
	FixedSListIterator iterator = *this;
	++*this;
	return iterator;
}


template<typename U>
bool FixedSListIterator<U>::operator!= (const FixedSListIterator<U>& iterator)
{
	return _CurrentNode != iterator._CurrentNode;
}


template<typename U>
typename U::value_type FixedSListIterator<U>::operator* ()
{
	return _CurrentNode->value;
}


} // namespace list
