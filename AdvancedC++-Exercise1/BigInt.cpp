#include "BigInt.h"
#include <iostream>
#include <string>
#include <limits>
#include <algorithm>


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

BigInt::BigInt() {}

BigInt BigInt::operator*(const BigInt & other)
{
	int i = 0;
	if (_data.size() > other._data.size())
		i = _data.size();
	else
		i = other._data.size();
	BigInt returnValue = BigInt();
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
		//returnValue+=base * base;
	}
	return returnValue;
}


BigInt::BigInt(const std::string& literals)
{
	if(!IsOnlyDigits(literals))
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


bool BigInt::IsOnlyDigits(const std::string& value) const
{
	std::string::const_iterator it = value.begin();
	if (*it == '-') {
		it++;
	}
	return std::all_of(it, value.end(), ::isdigit);
}


BigInt& BigInt::operator+= (const BigInt& other)
{
	return *this;
	// actual addition of rhs to *this
	/*
	if (_sign == other._sign) {

		BigInt res = other;
		for (int i = 0, carry = 0; i < (int)max(a.size(), v.a.size()) || carry; ++i) {
			if (i == (int)res.a.size())
				res.a.push_back(0);
			res.a[i] += carry + (i < (int)a.size() ? a[i] : 0);
			carry = res.a[i] >= base;
			if (carry)
				res.a[i] -= base;
		}
		return res;
	}
	else {
		return *this - (-other);
	}
	*/
}


BigInt& BigInt::operator-= (const BigInt& other)
{
	return *this;
	/*
	if (sign == v.sign) {
		if (abs() >= v.abs()) {
			bigint res = *this;
			for (int i = 0, carry = 0; i < (int)v.a.size() || carry; ++i) {
				res.a[i] -= carry + (i < (int)v.a.size() ? v.a[i] : 0);
				carry = res.a[i] < 0;
				if (carry)
					res.a[i] += base;
			}
			res.trim();
			return res;
		}
		return -(v - *this);
	}
	return *this + (-v);
	*/
}


BigInt BigInt::operator- () const 
{
	BigInt result;

	/*
	bigint res = *this;
	res.sign = -sign;
	return res;
	*/

	return result;
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


BigInt::~BigInt() {}
