namespace list {


template<class T, unsigned int N>
FixedSList<T, N>::FixedSList()
{
	_Root = &_Data[0];
	_Size = 0;
};


template<class T, unsigned int N>
FixedSList<T, N>::FixedSList(size_t n) // n should be minor of N
{
	value_type val = {};
	FixedSList aux(n, val);
	std::swap(_Data, aux._Data);
	std::swap(_Root, aux._Root);
	std::swap(_Size, aux._Size);
};


template<class T, unsigned int N>
FixedSList<T, N>::FixedSList(size_t n, const value_type& val) // n should be minor of N
{
	_Size = n;
	if (n > 0)
	{
		_Data[0] = val;
		_Root = &_Data[0];
	}
	for (size_t i = 1; i < n; ++i)
	{
		_Data[i] = val;
	}
};


template<class T, unsigned int N>
FixedSList<T, N>::FixedSList(iterator first, iterator last)//last - first should be minor of N
{
	if (first != last)
	{
		_Data[0] = *first;
		_Root = &_Data[0];
		_Size = 1;
		first++;
	}
	for (; first != last; ++first, ++_Size)
	{
		_Data[_Size] = *first;
	}
};

template<class T, unsigned int N>
FixedSList<T, N>::FixedSList(const FixedSList& x)
{
	_Size = x._Size;
	const_iterator it = x.cbegin();
	size_t rootIndex = x._Root - &_Data[0];
	if (_Size > 0)
	{
		_Data[rootIndex] = x._Data[0];
		_Root = &_Data[rootIndex];
		++rootIndex;
	}
	for (rootIndex; rootIndex < x._Size; ++rootIndex, ++it)
	{
		_Data[rootIndex] = x._Data[rootIndex];
	}
};


template<class T, unsigned int N>
FixedSList<T, N>::FixedSList(FixedSList&& x)
{
	std::swap(_Data, x._Data);
	_Root = &_Data[0];
	_Root+= x._Root - &x._Data[0];
	x._Root = nullptr;
	std::swap(_Size, x._Size);
};


template<class T, unsigned int N>
FixedSList<T, N>::FixedSList(std::initializer_list<value_type> il)
{
	_Root = nullptr;
	const value_type* it = il.begin(); //equivalent of std::initializer_list<value_type>::iterator
	_Size = il.size();
	if (_Size > 0)
	{
		_Data[0] = *it;
		_Root = &_Data[0];
		++it;
	}
	for (size_t i = 1; it != il.end(); ++it, ++i)
	{
		_Data[i] = *it;
	}
};


template<class T, unsigned int N>
FixedSList<T, N>::~FixedSList()
{
	for (size_t i = 0; i < _Size; ++i)
	{
		_Data[i].~value_type();
	}

	_Size = 0;
	_Root = nullptr;
};


template<class T, unsigned int N>
FixedSList<T, N>& FixedSList<T, N>::operator= (const FixedSList& x)
{
	for (size_t i = 0; i < _Size; ++i)
	{
		_Data[i].~value_type();
	}

	_Size = 0;
	_Root = nullptr;

	FixedSList aux(x);
	std::swap(*this, aux);
	return *this;
};


template<class T, unsigned int N>
FixedSList<T, N>& FixedSList<T, N>::operator= (FixedSList<T, N>&& x)
{
	for (size_t i = 0; i < _Size; ++i)
	{
		_Data[i].~value_type();
	}

	_Size = 0;
	_Root = nullptr;

	std::swap(*this, x);
	return *this;
};


template<class T, unsigned int N>
FixedSList<T, N>& FixedSList<T, N>::operator= (std::initializer_list<value_type> il)
{
	for (size_t i = 0; i < _Size; ++i)
	{
		_Data[i].~value_type();
	}

	_Size = 0;
	_Root = nullptr;

	FixedSList aux(il);
	std::swap(*this, aux);
	return *this;
};


template<class T, unsigned int N>
bool FixedSList<T, N>::empty() const
{
	return _Size <= 0;
};


template<class T, unsigned int N>
size_t FixedSList<T, N>::size() const
{
	return _Size;
};


template<class T, unsigned int N>
void FixedSList<T, N>::push_front(const value_type& val)
{
	if (_Root != &_Data[0])
	{

		T* oldRoot = _Root;
		--_Root;
		*_Root = val;
	}
	else
	{
		if (_Size < N)
		{
			for (int i = _Size; i >= 0; --i)
			{
				_Data[i + 1] = _Data[i];
			}
			_Data[0] = val;
			++_Size;
			_Root = &_Data[0];
		}
		else
		{
			throw std::out_of_range("index out of fixed list");
		}
	}
};


template<class T, unsigned int N>
void FixedSList<T, N>::push_front(value_type&& val)
{
	if (_Root != &_Data[0])
	{

		T* oldRoot = _Root;
		--_Root;
		std::swap(*_Root, val);
	}
	else
	{
		if (_Size < N)
		{
			for (int i = _Size; i >= 0; --i)
			{
				_Data[i + 1] = _Data[i];
			}
			std::swap(_Data[0], val);
			++_Size;
			_Root = &_Data[0];
		}
		else
		{
			throw std::out_of_range("index out of fixed list");
		}
	}
};


template<class T, unsigned int N>
void FixedSList<T, N>::pop_front()
{
	_Root->~value_type();
	++_Root;
	--_Size;
};


template<class T, unsigned int N>
void FixedSList<T, N>::push_back(const value_type& val)
{
	int forwardData = _Root - &_Data[0];
	if (forwardData + _Size < N)
	{
		_Data[_Size+ forwardData] =val;
		++_Size;
	}
	else
	{
		if (_Size < N)
		{
			size_t it = forwardData - 1;
			for (; it < _Size + forwardData - 1; ++it)
			{
				_Data[it] = _Data[it + 1];
			}
			_Data[it] = val;
			++_Size;
			--_Root;
		}
		else
		{
			throw std::out_of_range("index out of fixed list");
		}
	}
};


template<class T, unsigned int N>
void FixedSList<T, N>::push_back(value_type&& val)
{
	size_t forwardData = _Root - &_Data[0];
	if (forwardData + _Size < N)
	{
		_Data[_Size + forwardData] = val;
		++_Size;
	}
	else
	{
		if (_Size < N)
		{
			size_t it = forwardData-1;
			for (; it < _Size + forwardData-1; ++it)
			{
				_Data[it] = _Data[it + 1];
			}
			std::swap(_Data[it],val);
			++_Size;
			--_Root;
		}
		else
		{
			throw std::out_of_range("index out of fixed list");
		}
	}
};


template<class T, unsigned int N>
typename FixedSList<T, N>::iterator FixedSList<T, N>::begin()
{
	return iterator(_Root);
};


template<class T, unsigned int N>
typename FixedSList<T, N>::iterator FixedSList<T, N>::end()
{
	return iterator(_Root+_Size);
};


template<class T, unsigned int N>
typename FixedSList<T, N>::const_iterator FixedSList<T, N>::cbegin() const
{
	return const_iterator(_Root);
};


template<class T, unsigned int N>
typename FixedSList<T, N>::const_iterator FixedSList<T, N>::cend() const
{
	return const_iterator(_Root + _Size);
};


template<class T, unsigned int N>
typename FixedSList<T, N>::reverse_iterator FixedSList<T, N>::rbegin()
{
	return reverse_iterator(_Root);
};


template<class T, unsigned int N>
typename FixedSList<T, N>::reverse_iterator FixedSList<T, N>::rend()
{
	return reverse_iterator(_Root + _Size);
};


template<class T, unsigned int N>
typename FixedSList<T, N>::const_reverse_iterator FixedSList<T, N>::crbegin() const
{
	return const_reverse_iterator(_Root);
};


template<class T, unsigned int N>
typename FixedSList<T, N>::const_reverse_iterator FixedSList<T, N>::crend() const
{
	return const_reverse_iterator(_Root + _Size);
};


} // namespace list
