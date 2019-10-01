namespace list {


template<typename T>
SList<T>::SList()
{
	_Root = nullptr;
	_Size = 0;
};


template<typename T>
SList<T>::SList(size_t n)
{
	value_type val = {};
	SList aux(n, val);
	std::swap(_Size, aux._Size);
	std::swap(_Root, aux._Root);
};


template<typename T>
SList<T>::SList(size_t n, const value_type& val)
{
	_Root = nullptr;
	ListNode<T>* AuxNode = nullptr;
	_Size = n;
	if (n > 0)
	{
		_Root = new ListNode<T>();
		_Root->value = val;
		_Root->next = nullptr;
		AuxNode = _Root;
		--n;
	}
	for (; n > 0; --n)
	{
		AuxNode->next = new ListNode<T>();
		AuxNode = AuxNode->next;
		AuxNode->value = val;
	}
	AuxNode->next = nullptr;
};


template<typename T>
SList<T>::SList(iterator first, iterator last)
{
	_Root = new ListNode<T>();
	_Root->value = *first;
	_Root->next = nullptr;
	_Size = 1;
	ListNode<T>* AuxNode = _Root;
	first++;
	for (; first != last; ++first, ++_Size)
	{
		AuxNode->next = new ListNode<T>();
		AuxNode = AuxNode->next;
		AuxNode->value = *first;
	}
	AuxNode->next = nullptr;
};


template<typename T>
SList<T>::SList(const SList<T>& x)
{
	_Root = nullptr;
	ListNode<T>* AuxNode = _Root;
	const_iterator it = x.cbegin();
	_Size = x._Size;
	if (_Size > 0)
	{
		_Root = new ListNode<T>();
		_Root->value = *it;
		_Root->next = nullptr;
		AuxNode = _Root;
	}
	for (int i = 1; i < x._Size; ++i, ++it)
	{
		AuxNode->next = new ListNode<T>();
		AuxNode = AuxNode->next;
		AuxNode->value = *it;
	}
	AuxNode->next = nullptr;
};


template<typename T>
SList<T>::SList(SList<T>&& x)
{
	std::swap(_Root, x._Root);
	std::swap(_Size, x._Size);
};


template<typename T>
SList<T>::SList(std::initializer_list<value_type> il)
{
	_Root = nullptr;
	ListNode<T>* AuxNode = _Root;
	const value_type* it = il.begin(); //equivalent of std::initializer_list<value_type>::iterator
	_Size = il.size();
	if (il.size() > 0)
	{
		_Root = new ListNode<T>();
		_Root->value = *it;
		_Root->next = nullptr;
		AuxNode = _Root;
		++it;
	}
	for (; it != il.end(); ++it)
	{
		AuxNode->next = new ListNode<T>();
		AuxNode = AuxNode->next;
		AuxNode->value = *it;
	}
	AuxNode->next = nullptr;
};


template<typename T>
SList<T>::~SList()
{
	ListNode<T>* AuxNode = nullptr;
	for (; _Size > 0; _Size--)
	{
		AuxNode = _Root;
		_Root = _Root->next;
		AuxNode->value.~value_type();
		delete AuxNode;
	}
	delete _Root;
};


template<typename T>
SList<T>& SList<T>::operator= (const SList<T>& x)
{
	ListNode<T>* AuxNode = nullptr;
	for (; _Size > 0; _Size--)
	{
		AuxNode = _Root;
		_Root = _Root->next;
		AuxNode->value.~value_type();
		delete AuxNode;
	}
	SList aux(x);
	std::swap(*this, aux);
	return *this;
};


template<typename T>
SList<T>& SList<T>::operator= (SList&& x)
{
	ListNode<T>* AuxNode = nullptr;
	for (; _Size > 0; _Size--)
	{
		AuxNode = _Root;
		_Root = _Root->next;
		AuxNode->value.~value_type();
		delete AuxNode;
	}
	std::swap(*this, x);
	return *this;
};


template<typename T>
SList<T>& SList<T>::operator= (std::initializer_list<value_type> il)
{
	ListNode<T>* AuxNode = nullptr;
	for (; _Size > 0; _Size--)
	{
		AuxNode = _Root;
		_Root = _Root->next;
		AuxNode->value.~value_type();
		delete AuxNode;
	}
	SList aux(il);
	std::swap(*this, aux);
	return *this;
};


template<typename T>
bool SList<T>::empty() const
{
	return _Size <= 0;
};


template<typename T>
size_t SList<T>::size() const
{
	return _Size;
};


template<typename T>
void SList<T>::push_front(const value_type& val)
{
	ListNode<T>* NewElement = new ListNode<T>();
	NewElement->value = val;
	NewElement->next = _Root;
	_Root = NewElement;
	++_Size;
};


template<typename T>
void SList<T>::push_front(value_type&& val)
{
	ListNode<T>* NewElement = new ListNode<T>();
	std::swap(NewElement->value, val);
	NewElement->next = _Root;
	_Root = NewElement;
	++_Size;
};


template<typename T>
void SList<T>::pop_front()
{
	if (_Size > 0)
	{
		ListNode<T>* AuxNode = _Root;
		_Root = _Root->next;
		--_Size;
		AuxNode->value.~value_type();
		delete AuxNode;
	}
};


template<typename T>
void SList<T>::push_back(const value_type& val)
{
	if (_Size > 0)
	{
		ListNode<T>* NewElement = GetLast();

		NewElement->next = new ListNode<T>();
		NewElement = NewElement->next;
		NewElement->value = val;
		NewElement->next = nullptr;
		++_Size;
	}
	else
	{
		_Root = new ListNode<T>();
		_Root->value = val;
		_Root->next = nullptr;
		++_Size;
	}
};


template<typename T>
void SList<T>::push_back(value_type&& val)
{
	if (_Size > 0)
	{
		ListNode<T>* NewElement = GetLast();

		NewElement->next = new ListNode<T>();
		NewElement = NewElement->next;
		std::swap(NewElement->value, val);
		NewElement->next = nullptr;
		++_Size;
	}
	else
	{
		_Root = new ListNode<T>();
		std::swap(_Root->value, val);
		_Root->next = nullptr;
		++_Size;
	}
};


template<typename T>
typename SList<T>::iterator SList<T>::begin()
{
	return iterator(_Root);
};


template<typename T>
typename SList<T>::iterator SList<T>::end()
{
	return iterator(nullptr);
};


template<typename T>
typename SList<T>::const_iterator SList<T>::cbegin() const
{
	return const_iterator(_Root);
};


template<typename T>
typename SList<T>::const_iterator SList<T>::cend() const
{
	return const_iterator(nullptr);
};


template<typename T>
typename SList<T>::reverse_iterator SList<T>::rbegin()
{
	return reverse_iterator(_Root);
};


template<typename T>
typename SList<T>::reverse_iterator SList<T>::rend()
{
	return reverse_iterator(nullptr);
};


template<typename T>
typename SList<T>::const_reverse_iterator SList<T>::crbegin() const
{
	return const_reverse_iterator(_Root);
};


template<typename T>
typename SList<T>::const_reverse_iterator SList<T>::crend() const
{
	return const_reverse_iterator(nullptr);
};


template<typename T>
ListNode<T>* SList<T>::GetLast()
{
	ListNode<T>* Element = _Root;
	while (Element->next)
	{
		Element = Element->next;
	}
	return Element;
}



} // namespace list