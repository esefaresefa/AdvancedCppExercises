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


BigInt::BigInt(std::string literals)
{
	if (!IsOnlyDigits(literals) && literals.size()>1 && !IsOnlyDigits(literals.substr(1, literals.size())))
	{
		throw std::runtime_error("String is not a number");
	}

	size_t maxBlockDigits = MaxBlockDigits();

	int first = literals.size() - maxBlockDigits;
	int last = 0;
	if (literals[0] == '-')
	{
		_sign = true;
		last = 1;
	}
	if (literals[0] == '+')
	{
		last = 1;
	}

	// Reverse reading the string
	bool lastBlock = false;
	while (!lastBlock)
	{
		size_t count = maxBlockDigits;
		if (first <= last)
		{
			count = first + maxBlockDigits - last;
			first = last;
			lastBlock = true;
		}

		unsigned long block = stol(literals.substr(first, count));
		_data.push_back(block);
		first -= maxBlockDigits;
	}
}


BigInt& BigInt::operator*= (const BigInt & other)
{
	BigInt first = *this;
	_sign = first._sign ^ other._sign;
	_data.clear();
	_data.resize(first._data.size()+other._data.size()-1,0);
	for (int i = 0; i < first._data.size(); i++)
	{
		for (int j = 0; j < other._data.size(); j++) {
			unsigned long long int aux = static_cast<unsigned long long int>(first._data[i]) * static_cast<unsigned long long int>(other._data[j]);
			aux+= _data[i+j];
			if (aux <= MaxBlockValue())
			{
				_data[i+j] = static_cast<unsigned long int>(aux);
			}
			else
			{
				_data[i+j] = aux % (MaxBlockValue() + 1);
				if (_data.size() > i + j + 1)
				{
					_data[i + j +1] += aux / (MaxBlockValue() + 1); //carry
				}
				else
				{
					_data.push_back(aux / (MaxBlockValue() + 1)); //carry
				}

			}
		}
	}
	return *this;
}



BigInt& BigInt::operator+= (const BigInt& other)
{
	if (_sign == other._sign) 
	{
		BigInt result;

		size_t maxSize = std::max(_data.size(), other._data.size());
		for (size_t i = 0, carry = 0; i < maxSize || carry; i++) 
		{
			if (i == result._data.size())
			{
				result._data.push_back(0);
			}

			unsigned long long tmp = 0;
			tmp += i < other._data.size() ? other._data[i] : 0;
			tmp += i < _data.size() ? _data[i] : 0;
			tmp += carry;

			carry = tmp >= MaxBlockValue() + 1;
			
			if (carry)
			{
				tmp -= MaxBlockValue() + 1;
			}
			
			result._data[i] = tmp;
		}
		std::swap(*this, result);
	}
	else 
	{
		*this - (-other);
	}
	return *this;
}




BigInt& BigInt::operator-= (const BigInt& other)
{
	if (_sign == other._sign)
	{
		if (Abs() >= other.Abs())
		{
			unsigned long long tmp = 0;
			for (int i = 0, carry = 0; i < (int)other._data.size() || carry; ++i)
			{
				if (i < (int)other._data.size() && _data[i]>= other._data[i]+carry)
				{
					_data[i] -= carry + other._data[i];
					carry = false;
				}
				else
				{
					if (i < (int)other._data.size())
					{
						tmp += _data[i];
						tmp += MaxBlockValue()+ 1 + carry;
						if (i < (int)other._data.size())
						{
							tmp -= other._data[i];
						}
						_data[i] = tmp;
						carry = true;
					}
					else
					{
						_data[i] -= carry;
						carry = false;
					}
				}
			}

			Trim();
		}
		else
		{
			// Equivalent expression = -(other - *this)

			BigInt tmp(other);
			std::swap(*this, tmp);

			operator-= (tmp);
			_sign = !_sign;
		}
	}
	else
	{
		// Equivalent expression = *this += -other

		operator+= (-other);
	}

	return *this;
}


BigInt& BigInt::operator%= (const BigInt & other)
{
	_sign = false;
	if (*this >= other.Abs())
	{
		while ( *this >= other.Abs() && *this != 0)
		{
			*this -= other.Abs();
		}
	}
	else
	{
		BigInt aux = other;
		aux._sign = false;
		while (aux >= *this && aux != 0)
		{
			aux -= *this;
		}
		*this = aux;
	}
	return *this;
}


BigInt& BigInt::operator/= (const BigInt & other)
{
	bool sign = _sign;
	_sign = false;
	BigInt aux = *this;
	_data.clear();
	_data.push_back(0);
	if (aux >= other.Abs())
	{
		while (aux >= other.Abs() && aux!=0)
		{
			aux -= other.Abs();
			operator+=(1);
		}
	}
	else
	{
		BigInt aux2 = other.Abs();
		while (aux2 >= aux && aux2 != 0)
		{
			aux2 -= aux;
			operator+=(1);
		}
	}

	_sign = sign ^ other._sign;
	return *this;
}


BigInt BigInt::operator- () const 
{
	BigInt result = *this;
	result._sign = !_sign;
	return result;
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


BigInt& BigInt::operator--()
{
	*this -= 1;
	return *this;
}


BigInt BigInt::operator--(int)
{
	*this -= 1;
	return *this;
}


BigInt BigInt::operator<< (int steps) const
{ 
	BigInt result(*this);
	result <<= steps;
	return result;
};


BigInt& BigInt::operator<<= (int steps) 
{ 
	operator*= (pow(2, steps));
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
	operator/= (pow(2, steps));
	return *this;
};


bool BigInt::operator== (const BigInt & other) const
{
	return !(*this < other) && !(other < *this);
}


bool BigInt::operator!= (const BigInt & other) const
{
	return !(*this == other);
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

	for (int i = _data.size() - 1; i >= 0; i--)
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
	int minSize = _data.size() >= other._data.size() ? _data.size() - 1 : other._data.size() - 1;
	
	_data.erase(_data.begin() + minSize+1, _data.end());

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
		std::string numberToInsert = std::to_string(*it);
		while (numberToInsert.length() < MaxBlockDigits() && it!= _data.end()-1)
		{
			numberToInsert.insert(0,"0");
		}
		serialized.insert(0, numberToInsert);
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
	while (!_data.empty() && !_data.back()&& _data.size() >1)
	{
		_data.pop_back();
	}

	if (_data.size()==1 && !_data.back())
	{
		_sign = false;
	}
}


BigInt::~BigInt() {}
