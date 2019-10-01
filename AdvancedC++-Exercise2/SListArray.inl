namespace list {


template<typename T>
SListArray<T>::SListArray()
{
	_Root = nullptr;
	_Size = 0;
};


template<typename T>
SListArray<T>::SListArray(size_t n)
{
	value_type val = {};
	SListArray aux(n, val);
	std::swap(_Data, aux._Data);
	std::swap(_Root, aux._Root);
	std::swap(_Size, aux._Size);
};


template<typename T>
SListArray<T>::SListArray(size_t n, const value_type& val)
{
	_Data.resize(n);
	_Size = n;
	if (n > 0)
	{
		_Data[0].value = val;
		_Data[0].next = nullptr;
		_Root = &_Data[0];
	}
	for (size_t i = 1; i < n; ++i)
	{
		_Data[i - 1].next = &_Data[i];
		_Data[i].value = val;
		_Data[i].next = nullptr;
	}
};


template<typename T>
SListArray<T>::SListArray(iterator first, iterator last)
{
	size_t a = last - first;
	_Data.resize(last - first);
	if (first != last)
	{
		_Data[0].value = *first;
		_Data[0].next = nullptr;
		_Root = &_Data[0];
		_Size = 1;
		first++;
	}
	for (; first != last; ++first, ++_Size)
	{
		_Data[_Size - 1].next = &_Data[_Size];
		_Data[_Size].value = *first;
		_Data[_Size].next = nullptr;
	}
};


template<typename T>
SListArray<T>::SListArray(const SListArray& x)
{
	_Size = x._Size;
	_Data.resize(_Size);
	const_iterator it = x.cbegin();
	if (_Size > 0)
	{
		_Data[0].value=x._Data[0].value;
		_Data[0].next = nullptr;
		_Root = &_Data[0];
	}
	for (int i = 1; i < x._Size; ++i, ++it)
	{
		_Data[i - 1].next = &_Data[i];
		_Data[i].value = x._Data[i].value;
		_Data[i].next = nullptr;
	}
};


template<typename T>
SListArray<T>::SListArray(SListArray&& x)
{
	std::swap(_Root, x._Root);
	std::swap(_Size, x._Size);
	std::swap(_Data, x._Data);
};


template<typename T>
SListArray<T>::SListArray(std::initializer_list<value_type> il)
{
	_Root = nullptr;
	const value_type* it = il.begin(); //equivalent of std::initializer_list<value_type>::iterator
	_Size = il.size();
	_Data.resize(il.size());
	if (_Size > 0)
	{
		_Data[0].value = *it;
		_Data[0].next = nullptr;
		_Root = &_Data[0];
		++it;
	}
	for (size_t i = 1; it != il.end(); ++it, ++i)
	{
		_Data[i - 1].next = &_Data[i - 1];
		_Data[i].value = *it;
		_Data[i].next = nullptr;
	}
};


template<typename T>
SListArray<T>::~SListArray()
{
	_Size = 0;
	_Root = nullptr;
};


template<typename T>
SListArray<T>& SListArray<T>::operator= (const SListArray<T>& x)
{
	_Size = 0;
	_Root = nullptr;

	SListArray aux(x);
	std::swap(*this, aux);
	return *this;
};


template<typename T>
SListArray<T>& SListArray<T>::operator= (SListArray<T>&& x)
{
	_Size = 0;
	_Root = nullptr;

	std::swap(*this, x);
	return *this;
};


template<typename T>
SListArray<T>& SListArray<T>::operator= (std::initializer_list<value_type> il)
{
	_Size = 0;
	_Root = nullptr;

	SListArray aux(il);
	std::swap(*this, aux);
	return *this;
};


template<typename T>
bool SListArray<T>::empty() const
{
	return _Size <= 0;
};


template<typename T>
size_t SListArray<T>::size() const
{
	return _Size;
};


template<typename T>
void SListArray<T>::push_front(const value_type& val)
{
	_Data.insert(_Data.begin(), { val,_Root });
	_Root = &_Data[0];
	++_Size;
};


template<typename T>
void SListArray<T>::push_front(value_type&& val)
{
	ListNode<T> newNode = {};
	std::swap(newNode.value , val);
	newNode.next = _Root;
	_Data.insert(_Data.begin(), newNode);
	_Root = &_Data[0];
	++_Size;
};


template<typename T>
void SListArray<T>::pop_front()
{
	if (_Size > 0)
	{
		_Data[0].value.~value_type();
		_Data.erase(_Data.begin());
		_Root = &_Data[0];
		--_Size;
	}
};


template<typename T>
void SListArray<T>::push_back(const value_type& val)
{
	_Data.push_back({ val,nullptr });
	++_Size;
	if (_Size > 1)
	{
		_Data[_Size - 2].next = &_Data[_Size - 1];
	}
};


template<typename T>
void SListArray<T>::push_back(value_type&& val)
{
	ListNode<T> newNode{ val, nullptr };
	//std::swap(newNode.val, val);
	_Data.push_back({ newNode });
	++_Size;
	if (_Size > 1)
	{
		_Data[_Size - 2].next = &_Data[_Size - 1];
	}
};


template<typename T>
typename SListArray<T>::iterator SListArray<T>::begin()
{
	return iterator(&_Data[0]);
};


template<typename T>
typename SListArray<T>::iterator SListArray<T>::end()
{
	return iterator(&_Data[_Size - 1] + 1);
};


template<typename T>
typename SListArray<T>::const_iterator SListArray<T>::cbegin() const
{
	return const_iterator(&_Data[0]);
};


template<typename T>
typename SListArray<T>::const_iterator SListArray<T>::cend() const
{
	return const_iterator(&_Data[_Size - 1] + 1);
};


template<typename T>
typename SListArray<T>::reverse_iterator SListArray<T>::rbegin()
{
	return reverse_iterator(&_Data[0]);
};


template<typename T>
typename SListArray<T>::reverse_iterator SListArray<T>::rend()
{
	return reverse_iterator(&_Data[_Size - 1] + 1);
};


template<typename T>
typename SListArray<T>::const_reverse_iterator SListArray<T>::crbegin() const
{
	return const_reverse_iterator(&_Data[0]);
};


template<typename T>
typename SListArray<T>::const_reverse_iterator SListArray<T>::crend() const
{
	return const_reverse_iterator(&_Data[_Size - 1] + 1);
};



} // namespace list