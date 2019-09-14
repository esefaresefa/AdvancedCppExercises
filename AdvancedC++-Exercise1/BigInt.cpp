#include "BigInt.h"
#include <iostream>
#include <string>
#include <limits>
#include <algorithm>


BigInt::BigInt() {}


BigInt::BigInt(int integer)
{
	if (integer < 0)
	{
		_sign = true;
		_data = std::vector<unsigned long int>();
		_data.push_back(-integer);
	}
	else
	{

		_sign = false;
		_data = std::vector<unsigned long int>();
		_data.push_back(integer);
	}
}


BigInt::BigInt(const std::string& literals)
{
	if (!IsOnlyDigits(literals))
	{
		throw std::runtime_error("String is not a number");
	}

	size_t first = 0;
	size_t last = 0;
	if (literals[0] == '-')
	{
		_sign = true;
		first++;
	}

	while (first < literals.size())
	{
		unsigned long block = stol(literals.substr(first, MaxBlockDigits()));
		_data.push_back(block);
		first += MaxBlockDigits();
	}

	// Reverse order to mantain the lowest digits at the lowest indices
	std::reverse(_data.begin(), _data.end());
}


BigInt BigInt::operator* (const BigInt & other)
{
	size_t i = 0;
	if (_data.size() > other._data.size())
		i = _data.size();
	else
		i = other._data.size();
	BigInt returnValue = BigInt();
	returnValue._sign = _sign ^ other._sign;
	unsigned long long int carry = 0;
	for (; i > 0; i--)
	{
		unsigned long long int aux = _data[i] * other._data[i];
		aux += carry;
		if (aux <= MaxBlockValue())
		{
			returnValue._data.insert(_data.begin(), static_cast<unsigned long int>(aux));
			carry = 0;
		}
		else
		{
			returnValue._data.insert(_data.begin(), aux%(MaxBlockValue()+1));
			carry = aux/(MaxBlockValue() + 1);
		}
	}
	return returnValue;
}

BigInt BigInt::Power(BigInt base, int exponent)
{

	BigInt returnValue = BigInt();
	for (int i = 0; i < exponent; i++)
	{
		returnValue+=base * base;
	}
	return returnValue;
}


/*
BigInt& BigInt::operator= (const BigInt & other)
{

	_sign = other._sign;
	_data = std::vector<unsigned long int>(other._data);
	return *this;
}
*/


BigInt& BigInt::operator+= (const BigInt& other)
{
	// actual addition of rhs to *this
	if (_sign == other._sign) {
				
		for (int i = 0, carry = 0; i < static_cast<int>(std::max(_data.size(), other._data.size())) || carry; ++i) 
		{
			if (i == (int)_data.size())
			{
				_data.push_back(0);
			}

			_data[i] += carry + (i < (int)_data.size() ? _data[i] : 0);
			carry = _data[i] >= MaxBlockValue();
			
			if (carry)
			{
				_data[i] -= MaxBlockValue();
			}
		}
	}
	else 
	{
		operator-= (-other);
	}

	return *this;
}


BigInt& BigInt::operator*= (const BigInt& other)
{
	return *this;
}


BigInt& BigInt::operator% (const BigInt & other)
{
	if (*this >= other)
	{
		for (; *this >= other; *this -= other);
		{}
		return *this;
	}
	else
	{
		BigInt returnValue = other;
		for (; returnValue>= *this;  returnValue -= *this);
		{}
		return returnValue; // TODO(mattia) BUG!
	}
}


BigInt& BigInt::operator/ (const BigInt & other)
{
	BigInt returnValue = BigInt();
	if (_data.size() > other._data.size())
	{
		for (returnValue = 0; *this >= other; *this -= other, returnValue++);
	}
	else
	{
		BigInt aux = other;
		for (; aux >= *this; aux -= *this, returnValue++);
	}
	return returnValue; // TODO(mattia) BUG!
}


BigInt& BigInt::operator%=(const BigInt & other)
{
	return *this = *this%other;
}


BigInt& BigInt::operator/=(const BigInt & other)
{
	return *this = *this/other;
}


BigInt& BigInt::operator++()
{
	*this += 1;
	return *this;
}


BigInt BigInt::operator++(int)
{
	*this += 1;
	return *this;
}


BigInt& BigInt::operator-= (const BigInt& other)
{
	if (_sign == other._sign) 
	{	
		if (Abs() >= other.Abs()) 
		{

			for (int i = 0, carry = 0; i < (int)other._data.size() || carry; ++i) {

				_data[i] -= carry + (i < (int)other._data.size() ? other._data[i] : 0);

				carry = _data[i] < 0;
				if (carry)
				{
					_data[i] += MaxBlockValue();
				}
			}
			
			Trim();
		}
		else 
		{
			// Equivalent expression
			// -(other - *this)

			BigInt tmp(other);
			std::swap(*this, tmp);

			operator-= (tmp);
			_sign = !_sign;
		}
	}
	else 
	{
		// Equivalent expression
		// *this += -other

		operator+= (-other);
	}

	return *this;
}


BigInt BigInt::operator- () const 
{
	BigInt result = *this;
	result._sign = !_sign;
	return result;
}


BigInt BigInt::operator<< (int steps) const
{ 
	BigInt result(*this);
	result <<= steps;
	return result;
};


// TODO(luca) BUG!
BigInt& BigInt::operator<<= (int steps) 
{ 
	int lastDigits = 0;
	for (size_t index = 0; index < _data.size(); index++)
	{
		_data[index] += lastDigits;
		if (index - 1 >= 0) {
			int lastDigits = _data[index++] / (10 * steps);
		}
		_data[index] <<= steps;
	}

	return *this;
};


BigInt BigInt::operator>> (int steps) const
{ 
	BigInt result(*this);
	result >>= steps;
	return result;
};


BigInt& BigInt::operator>>= (int steps)
{ 
	/* TODO(luca) */ 
	return *this;
};


bool BigInt::operator== (const BigInt & other) const
{
	return !(*this < other) && !(other < *this);
}


bool BigInt::operator> (const BigInt & other) const
{
	return other < *this;
}


bool BigInt::operator< (const BigInt & other) const
{
	if (_sign != other._sign)
	{
		return GetSign() < other.GetSign();
	}

	if (_data.size() != other._data.size())
	{
		return _data.size() * GetSign() < other._data.size() * other.GetSign();
	}

	for (size_t i = _data.size() - 1; i >= 0; i--)
	{
		if (_data[i] != other._data[i])
		{
			return _data[i] * GetSign() < other._data[i] * GetSign();
		}
	}

	return false;
}


bool BigInt::operator>= (const BigInt & other) const
{
	return !(*this < other);
}


bool BigInt::operator<= (const BigInt & other) const
{
	return !(other < *this);
}


BigInt& BigInt::operator&= (const BigInt & other)
{
	size_t minSize = _data.size() >= other._data.size() ? _data.size() - 1 : other._data.size() - 1;
	
	_data.erase(_data.begin() + minSize, _data.end());

	for (; minSize >= 0; minSize--)
	{
		_data[minSize] = _data[minSize] & other._data[minSize];
	}

	return *this;
}


BigInt & BigInt::operator|= (const BigInt & other)
{
	size_t minSize = _data.size() >= other._data.size() ? _data.size() - 1 : other._data.size() - 1;
	for (; minSize >= 0; minSize--)
	{
		_data[minSize] = _data[minSize] & other._data[minSize];
	}
	
	return *this;
}


BigInt & BigInt::operator^= (const BigInt & other)
{
	size_t minSize = _data.size() >= other._data.size() ? _data.size() - 1 : other._data.size() - 1;
	for (; minSize >= 0; minSize--)
	{
		_data[minSize] = _data[minSize] ^ other._data[minSize];
	}

	return *this;
}


std::string BigInt::ToString() const 
{
	std::string serialized;
	for (auto it = _data.begin(); it != _data.end(); it++)
	{
		serialized.insert(0, std::to_string(*it));
	}

	// Add the sign in top of the number
	if (_sign)
	{
		serialized.insert(0, "-");
	}

	return serialized;
}


BigInt BigInt::Abs() const 
{
	BigInt result(*this);
	result._sign = false;

	return result;
}


int BigInt::GetSign() const
{
	return _sign == true ? -1 : 1;
}


bool BigInt::IsOnlyDigits(const std::string& value) const
{
	std::string::const_iterator it = value.begin();
	if (*it == '-') {
		it++;
	}
	return std::all_of(it, value.end(), ::isdigit);
}


void BigInt::Trim()
{
	while (!_data.empty() && !_data.back())
	{
		_data.pop_back();
	}

	if (_data.empty())
	{
		_sign = false;
	}
}


BigInt::~BigInt() {}
