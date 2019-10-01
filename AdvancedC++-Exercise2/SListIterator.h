#pragma once


namespace list {


template<typename U>
class SListIterator {

public:

	SListIterator();

	SListIterator(typename U* pNode);

	SListIterator& operator= (U* pNode);

	// Prefix ++ overload 
	SListIterator& operator++();

	// Postfix ++ overload 
	SListIterator operator++(int);

	bool operator!=(const SListIterator& iterator);

	bool operator==(const SListIterator& iterator);

	typename U::value_type operator*();

	U GetNode();

private:

	U* _CurrentNode;

};



template<typename U>
SListIterator<U>::SListIterator() : _CurrentNode(nullptr)
{ }



template<typename U>
SListIterator<U>::SListIterator(U* node) : _CurrentNode(node)
{ }


template<typename U>
SListIterator<U>& SListIterator<U>::operator= (U* node)
{
	this->_CurrentNode = node;
	return *this;
}


template<typename U>
SListIterator<U>& SListIterator<U>::operator++ ()
{
	if (_CurrentNode)
		_CurrentNode = _CurrentNode->next;
	return *this;
}


template<typename U>
SListIterator<U> SListIterator<U>::operator++ (int)
{
	SListIterator iterator = *this;
	++*this;
	return iterator;
}


template<typename U>
bool SListIterator<U>::operator!= (const SListIterator<U>& iterator)
{
	return _CurrentNode != iterator._CurrentNode;
}


template<typename U>
bool SListIterator<U>::operator== (const SListIterator<U>& iterator)
{
	return !(_CurrentNode != iterator._CurrentNode);
}


template<typename U>
typename U::value_type SListIterator<U>::operator* ()
{
	return _CurrentNode->value;
}

template<typename U>
typename U SListIterator<U>::GetNode()
{
	return *this->_CurrentNode;
}


} // namespace list
