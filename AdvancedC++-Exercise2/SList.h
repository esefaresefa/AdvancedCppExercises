#pragma once

#include "SListIterator.h"
#include "ListNode.h"
#include <iterator>


namespace list {

	   	  
template<typename T>
class SList
{

public:

	typedef T value_type;
	typedef T& reference_type;
	typedef const T& const_reference_type;

	typedef SListIterator<ListNode<T>> iterator;
	typedef SListIterator<const ListNode<T>> const_iterator;
	typedef std::reverse_iterator<SListIterator<T>> reverse_iterator;
	typedef std::reverse_iterator<const SListIterator<T>> const_reverse_iterator;
	
	// Constructors
	explicit SList() 
	{
		_Root = nullptr;
		_Size = 0;
	};

	explicit SList(size_t n)
	{
		value_type val = {};
		SList aux(n, val);
		std::swap(_Size, aux._Size);
		std::swap(_Root, aux._Root);
	};

	SList(size_t n, const value_type& val)
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

	SList(iterator first, iterator last)
	{
		_Root = new ListNode<T>();
		_Root->value = *first;
		_Root->next = nullptr;
		_Size = 1;
		ListNode<T>* AuxNode = _Root;
		first++;
		for (;first!=last;++first,++_Size)
		{
			AuxNode->next = new ListNode<T>();
			AuxNode = AuxNode->next;
			AuxNode->value = *first;
		}
		AuxNode->next = nullptr;
	};

	SList(const SList& x)
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
		for (int i=1; i < x._Size; ++i, ++it)
		{
			AuxNode->next = new ListNode<T>();
			AuxNode = AuxNode->next;
			AuxNode->value = *it;
		}
		AuxNode->next = nullptr;
	};

	SList(SList&& x)
	{
		std::swap(_Root, x._Root);
		std::swap(_Size, x._Size);
	};

	SList(std::initializer_list<value_type> il)
	{
		_Root = nullptr;
		ListNode<T>* AuxNode = _Root;
		const value_type* it = il.begin(); //equivalent of std::initializer_list<value_type>::iterator
		_Size = il.size();
		if (il.size()>0)
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


	// Destructor
	virtual ~SList() 
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


	// Asignment operators
	SList& operator= (const SList& x)
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

	SList& operator= (SList&& x) 
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

	SList& operator= (std::initializer_list<value_type> il)
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


	// Capacity
	bool empty() const 
	{
		return _Size <= 0;
	};

	size_t size() const
	{
		return _Size;
	};


	// Access operators
	ListNode<T>& front()
	{
		return *_Root;
	}

	ListNode<T>& back()
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


	// Modifiers
	void push_front(const value_type& val)
	{
		ListNode<T>* NewElement = new ListNode<T>();
		NewElement->value = val;
		NewElement->next = _Root;
		_Root = NewElement;
		++_Size;
	};

	void push_front(value_type&& val) 
	{
		ListNode<T>* NewElement = new ListNode<T>();
		std::swap(NewElement->value, val);
		NewElement->next = _Root;
		_Root = NewElement;
		++_Size;
	};

	void pop_front() 
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

	void push_back(const value_type& val)
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

	void push_back(value_type&& val) 
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
			std::swap(_Root->value , val);
			_Root->next = nullptr;
			++_Size;
		}
	};

	void pop_back()
	{
		if (_Size > 0)
		{
			// if last node in list
			if (_Root->next == nullptr)
			{
				--_Size;
				_Root->value.~value_type();
				delete _Root;
			}
			// if there is more than one node
			else
			{
				ListNode<T>* AuxNode = _Root;

				while ((AuxNode->next)->next != nullptr)
				{
					AuxNode = AuxNode->next;
				}

				--_Size;
				(AuxNode->next)->value.~value_type();
				delete AuxNode->next;
				AuxNode->next = nullptr;
			}

		}
	}

	iterator insert(iterator pos, const T& value)
	{
		iterator PrecIt = _Root;

		// maintain list order
		//error
		while (PrecIt._CurrentNode->next != pos._CurrentNode)
		{
			PrecIt++;
		}

		// insert element
		ListNode<T>* NewElement = new ListNode<T>();
		NewElement->value = value;
		NewElement->next = pos._CurrentNode;

		PrecIt._CurrentNode->next = NewElement;

		_Size++;

		return PrecIt;
	}

	iterator erase(iterator pos)
	{
		iterator PrecIt = _Root;

		// maintain list order
		//error
		while (PrecIt._CurrentNode->next != pos._CurrentNode)
		{
			PrecIt++;
		}
		PrecIt._CurrentNode->next = pos._CurrentNode->next;

		// delete node in pos
		pos._CurrentNode->value.~value_type();
		delete pos._CurrentNode;

		_Size--;

		return ++PrecIt;
	}

	iterator erase(iterator first, iterator last)
	{
		iterator PrecIt = _Root;

		// maintain list order
		while (PrecIt._CurrentNode->next != first._CurrentNode)
		{
			PrecIt++;
		}
		PrecIt._CurrentNode->next = last._CurrentNode->next;

		iterator Prec_PrecIt = first._CurrentNode;
		// delete first to last nodes
		while (first != last)
		{
			Prec_PrecIt = first._CurrentNode;

			first._CurrentNode->value.~value_type();
			first++;

			delete Prec_PrecIt._CurrentNode;

			_Size--;
		}
		last._CurrentNode->value.~value_type();
		delete last._CurrentNode;

		_Size--;

		return ++PrecIt;
	}


	void resize(size_t count, const value_type& value)
	{
		ListNode<T>* AuxNode = _Root;
		ListNode<T>* LastNode = AuxNode;
		int iter = 0;

		// decrease list
		if (_Size > count)
		{
			for (iter; iter < count; iter++)
			{
				AuxNode = AuxNode->next;
			}

			LastNode = AuxNode;
			
			iterator PrecIt = AuxNode;

			// delete extra nodes
			for (iter; iter < _Size; iter++)
			{
				//error
				PrecIt = AuxNode;

				AuxNode->value.~value_type();
				AuxNode = AuxNode->next;

				delete PrecIt._CurrentNode;
			}
				
		}
		// increase list
		else if (_Size < count)
		{
			for (iter; iter < _Size-1; iter++)
			{
				AuxNode = AuxNode->next;
			}

			// add extra nodes
			for (iter; iter < count-1; iter++)
			{
				AuxNode->value = value;
				AuxNode->next = new ListNode<T>();
				AuxNode = AuxNode->next;
			}

			LastNode = AuxNode;

		}

		LastNode = nullptr;
		_Size = count;
	}

	void resize(size_t count)
	{
		resize(count, 0);
	}

	void clear()
	{
		iterator it = _Root;
		iterator PrecIt = it;

		while (it._CurrentNode != nullptr)
		{
			PrecIt = it;

			it._CurrentNode->value.~value_type();
			it._CurrentNode = it._CurrentNode->next;

			delete PrecIt._CurrentNode;
		}

		_Root->next = nullptr;
		_Root = nullptr;
		_Size = 0;
	}



	iterator begin() 
	{ 
		return iterator(_Root); 
	};

	iterator end() 
	{ 
		return iterator(nullptr); 
	};

	const_iterator cbegin() const
	{ 
		return const_iterator(_Root); 
	};

	const_iterator cend() const
	{ 
		return const_iterator(nullptr); 
	};

	reverse_iterator rbegin()
	{
		return reverse_iterator(_Root);
	};

	const_reverse_iterator rend() const
	{
		return const_reverse_iterator(nullptr);
	};

protected:

	ListNode<T>* GetLast() 
	{
		ListNode<T>* Element = _Root;
		while (Element->next)
		{
			Element = Element->next;
		}
		return Element;
	}

private:

	ListNode<T>* _Root;
	size_t _Size;

};



} // namespace list