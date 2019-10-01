#pragma once


namespace list {


template<typename U>
class SListArrayIterator {

	typedef U value_type;
	typedef U& reference_type;
	typedef U* pointer_type;
	typedef const U& const_reference_type;

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

	typename U GetNode();

	template<typename U>
	friend size_t operator-(const SListArrayIterator<U>& lhs, const SListArrayIterator<U>& rhs);

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
		_CurrentNode++;
	return *this;
}


template<typename U>
SListArrayIterator<U> SListArrayIterator<U>::operator++ (int)
{
	SListArrayIterator iterator(*this);
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

template<typename U>
size_t operator-(const SListArrayIterator<U>& lhs, const SListArrayIterator<U>& rhs)
{
	size_t count = std::distance(rhs._CurrentNode, lhs._CurrentNode);
	return count;
}

template<typename U>
typename U SListArrayIterator<U>::GetNode()
{
	return *this->_CurrentNode;
}


} // namespace list
