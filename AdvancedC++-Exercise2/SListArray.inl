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
	_Root = nullptr;
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
	_Root = nullptr;
	if (first != last)
	{
		push_back(*first);
		_Root = &_Data[0];
		first++;
	}
	for (; first != last; ++first)
	{
		push_back(*first);
	}
};


template<typename T>
SListArray<T>::SListArray(const SListArray& x)
{
	_Size = x._Size;
	_Data.resize(_Size);
	_Root = nullptr;
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
		_Data[i - 1].next = &_Data[i];
		_Data[i].value = *it;
		_Data[i].next = nullptr;
	}
};


template<typename T>
SListArray<T>::~SListArray()
{
	_Data.clear();
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



// Member access
template<typename T>
ListNode<T>& SListArray<T>::front()
{
	return *_Root;
}

template<typename T>
ListNode<T>& SListArray<T>::back()
{
	if (_Root == nullptr)
		return *_Root;

	ListNode<T>* AuxNode = _Root;

	while (AuxNode->next != nullptr)
	{
		AuxNode = AuxNode->next;
	}

	return *AuxNode;
}

template<typename T>
void SListArray<T>::push_front(const value_type& val)
{
	if (_Data.size() <_Data.capacity()  || _Root == nullptr)
	{
		_Data.push_back({ val , _Root });
		_Root = &_Data[_Data.size()-1];
		_Size++;
	}
	else 
	{

		ListNode<T>* AuxNode = _Root;

		std::vector<ListNode<T>> auxData(_Size + 1); 
		size_t i = 0;
		auxData[i] = { val , &auxData[i+1]};
		++i;
		for (; AuxNode->next != nullptr; ++i)
		{
			auxData[i] = { AuxNode->value , &auxData[i + 1] };
			AuxNode = AuxNode->next;
		}
		auxData[i] = { AuxNode->value ,nullptr };
		_Data.clear();
		_Data = std::move(auxData);
		_Root = &_Data[0];
		++_Size;
	}
};


template<typename T>
void SListArray<T>::push_front(value_type&& val)
{
	if (_Data.size() < _Data.capacity() || _Root == nullptr)
	{
		_Data.push_back({ T{} , _Root });
		std::swap(_Data[_Data.size() - 1].value,val);
		_Root = &_Data[_Data.size()-1];
		_Size++;
	}
	else
	{

		ListNode<T>* AuxNode = _Root;

		std::vector<ListNode<T>> auxData(_Size + 1);
		size_t i = 0;
		auxData[i] = { T{} , &auxData[i + 1] };
		std::swap(auxData[i].value, val);
		++i;
		for (; AuxNode->next != nullptr; ++i)
		{
			auxData[i] = { AuxNode->value , &auxData[i + 1] };
			AuxNode = AuxNode->next;
		}
		auxData[i] = { AuxNode->value ,nullptr };
		_Data.clear();
		_Data = std::move(auxData);
		_Root = &_Data[0];
		++_Size;
	}
};


template<typename T>
void SListArray<T>::pop_front()
{
	ListNode<T>* DeleteNode = _Root;
	_Root = _Root->next;
	DeleteNode->value.~value_type();
	--_Size;
};


template<typename T>
void SListArray<T>::push_back(const value_type& val)
{
	if (_Data.size() < _Data.capacity() || _Root == nullptr)
	{
		_Data.push_back({ val , nullptr });
		_Size++;
		if (_Root == nullptr)
		{
			_Root = &_Data[0];
		}
	}
	else
	{

		ListNode<T>* AuxNode = _Root;

		std::vector<ListNode<T>> auxData(_Size + 1);
		size_t i = 0;
		for (; AuxNode != nullptr; ++i)
		{
			auxData[i] = { AuxNode->value , &auxData[i + 1] };
			AuxNode = AuxNode->next;
		}
		auxData[i] = { val , nullptr };
		_Data.clear();
		_Data = std::move(auxData);
		_Root = &_Data[0];
		++_Size;
	}
};


template<typename T>
void SListArray<T>::push_back(value_type&& val)
{
	if (_Data.size() < _Data.capacity() || _Root == nullptr)
	{
		_Data.push_back({ T{} , nullptr });
		std::swap(_Data[_Data.size() - 1].value, val);
		_Size++;
		if (_Root == nullptr)
		{
			_Root = &_Data[0];
		}
	}
	else
	{

		ListNode<T>* AuxNode = _Root;

		std::vector<ListNode<T>> auxData(_Size + 1);
		size_t i = 0;
		for (; AuxNode != nullptr; ++i)
		{
			auxData[i]={ AuxNode->value , &auxData[i + 1] };
			AuxNode = AuxNode->next;
		}
		auxData[i] = { T{} , nullptr };
		std::swap(auxData[i].value, val);
		_Data.clear();
		_Data = std::move(auxData);
		_Root = &_Data[0];
		++_Size;
	}
};


template<typename T>
void SListArray<T>::pop_back()
{
	if (_Size > 0)
	{
		// if last node in list
		if (_Root->next == nullptr)
		{
			_Root->value.~value_type();
			_Data.pop_back();
			--_Size;
			_Root = nullptr;
		}
		// if there is more than one node
		else
		{

			ListNode<T>* AuxNode = _Root;

			while (AuxNode->next->next != nullptr)
			{
				AuxNode = AuxNode->next;
			}
			AuxNode->next->value.~value_type();
			AuxNode->next = nullptr;
			--_Size;
		}
	}
}


template<typename T>
typename SListArray<T>::iterator SListArray<T>::insert(iterator pos, const T& value)
{
	iterator PrecIt = _Root;
	ListNode<T>* aux = _Root;

	// if pos == begin()
	if (pos == begin())
	{
		push_front(value);
		return PrecIt;
	}
	if (pos == end())
	{
		PrecIt = &back();
		push_back(value);
	}
	else
	{
		if (_Data.size() < _Data.capacity())
		{
			// maintain list order
			//error
			while (iterator(aux->next) != pos)
			{
				PrecIt++;
				aux = aux->next;
			}

			_Data.push_back({ value , aux->next });
			aux->next = &_Data[_Data.size()-1];
			_Size++;
		}
		else
		{
			std::vector<ListNode<T>> auxData(_Size + 1);
			size_t i = 0;
			for (; iterator(aux) != pos; ++i)
			{
				auxData[i]={ aux->value , &auxData[i + 1] };
				PrecIt++;
				aux = aux->next;
			}

			auxData[i] = { value , &auxData[i + 1] };
			++i;
			for (; iterator(aux->next) != nullptr; ++i)
			{
				auxData[i] = { aux->value , &auxData[i + 1] };
				aux = aux->next;
			}
			auxData[i] = { aux->value , nullptr };
			_Data.clear();
			_Data = std::move(auxData);
			_Root = &_Data[0];
			_Size++;
		}
	}

	return PrecIt;
}


template<typename T>
typename SListArray<T>::iterator SListArray<T>::erase(iterator pos)
{
	iterator PrecIt = _Root;
	ListNode<T>* aux = _Root;

	// if pos == begin()
	if (pos == PrecIt)
	{
		pop_front();
		return ++PrecIt;
	}
	if (pos == end())
	{
		pop_back();
		PrecIt = &back();
	}
	else
	{
		// maintain list order
		//error
		while (iterator(aux->next) != pos)
		{
			PrecIt++;
			aux = aux->next;
		}

		ListNode<T>* deleteNode = aux->next;
		aux->next = aux->next->next;

		// delete node in pos
		deleteNode->value.~value_type();
		deleteNode = nullptr;

		_Size--;
	}

	return ++PrecIt;
}


template<typename T>
typename SListArray<T>::iterator SListArray<T>::erase(iterator first, iterator last)
{
	iterator PrecIt = _Root;
	ListNode<T>* aux = _Root;

	// maintain list order
	while (iterator(aux->next) != first)
	{
		PrecIt++;
		aux = aux->next;
	}
	ListNode<T>* lastNode = aux->next;
	ListNode<T>* deleteNode = lastNode;

	while (iterator(lastNode) != last)
	{
		deleteNode = lastNode;
		lastNode = lastNode->next;
		deleteNode->value.~value_type();
		deleteNode->next=nullptr;

		_Size--;
	}
	aux->next = lastNode->next;
	lastNode->value.~value_type();
	_Size--;
	return ++PrecIt;
}


template<typename T>
void SListArray<T>::resize(size_t count, const value_type& value)
{
	_Data.resize(count, { value, nullptr });
	_Size = count;
	_Root = &_Data[0];
	for (size_t i = 0; i < _Size-1; i++)
	{
		_Data[i].next = &_Data[i + 1];
	}
	_Data[_Size - 1].next = nullptr;
}


template<typename T>
void SListArray<T>::resize(size_t count)
{
	resize(count, T{});
}


template<typename T>
void SListArray<T>::clear()
{
	_Data.clear();
	_Root = nullptr;
	_Size = 0;
}


template<typename T>
typename SListArray<T>::iterator SListArray<T>::begin()
{
	if (_Size > 0)
		return iterator(_Root);

	return iterator(nullptr);

};


template<typename T>
typename SListArray<T>::iterator SListArray<T>::end()
{
	return iterator(nullptr);
};


template<typename T>
typename SListArray<T>::const_iterator SListArray<T>::cbegin() const
{
	if (_Size > 0)
		return const_iterator(_Root);

	return const_iterator(nullptr);
};


template<typename T>
typename SListArray<T>::const_iterator SListArray<T>::cend() const
{
	return const_iterator(nullptr);
};


template<typename T>
typename SListArray<T>::reverse_iterator SListArray<T>::rbegin()
{
	return reverse_iterator(_Root);
};


template<typename T>
typename SListArray<T>::reverse_iterator SListArray<T>::rend()
{
	return reverse_iterator(nullptr);
};


template<typename T>
typename SListArray<T>::const_reverse_iterator SListArray<T>::crbegin() const
{
	return const_reverse_iterator(_Root);
};


template<typename T>
typename SListArray<T>::const_reverse_iterator SListArray<T>::crend() const
{
	return const_reverse_iterator(nullptr);
};



} // namespace list