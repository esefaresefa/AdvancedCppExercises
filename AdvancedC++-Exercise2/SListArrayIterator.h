#pragma once


namespace list {


template<typename U>
class SListArrayIterator {

public:

	SListArrayIterator();

	SListArrayIterator(typename U* pNode);

	SListArrayIterator& operator= (U* pNode);

	// Prefix ++ overload 
	SListArrayIterator& operator++();

	// Postfix ++ overload 
	SListArrayIterator operator++(int);

	bool operator!=(const SListArrayIterator& iterator);

	typename U::value_type operator*();

private:

	U* _CurrentNode;
};



template<typename U>
SListArrayIterator<U>::SListArrayIterator() : _CurrentNode(nullptr)
{ }



template<typename U>
SListArrayIterator<U>::SListArrayIterator(U* node) : _CurrentNode(node)
{ }


template<typename U>
SListArrayIterator<U>& SListArrayIterator<U>::operator= (U* node)
{
	this->_CurrentNode = node;
	return *this;
}


template<typename U>
SListArrayIterator<U>& SListArrayIterator<U>::operator++ ()
{
	if (_CurrentNode)
		_CurrentNode = _CurrentNode->next;
	return *this;
}


template<typename U>
SListArrayIterator<U> SListArrayIterator<U>::operator++ (int)
{
	SListArrayIterator iterator = *this;
	++*this;
	return iterator;
}


template<typename U>
bool SListArrayIterator<U>::operator!= (const SListArrayIterator<U>& iterator)
{
	return _CurrentNode != iterator._CurrentNode;
}


template<typename U>
typename U::value_type SListArrayIterator<U>::operator* ()
{
	return _CurrentNode->value;
}


} // namespace list
