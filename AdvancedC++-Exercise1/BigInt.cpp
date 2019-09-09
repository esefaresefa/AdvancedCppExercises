#include "BigInt.h"
#include <iostream>
#include <string>
#include <limits>
#include <algorithm>


BigInt::BigInt() {}


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
		unsigned long long block = stoll(literals.substr(first, MaxBlockDigits()));
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


BigInt BigInt::operator+ (const BigInt& other)
{
	BigInt returnValue;

	unsigned long long int carry = 0;
	for (size_t i = 0; i < other._data.size(); i++) 
	{
		// TODO(luca)
	}

	return returnValue;
}


unsigned long long int BigInt::Carry(unsigned long long int a, unsigned long long int b) const
{
	// TODO(luca)
	return 0;
}


std::ostream& operator<< (std::ostream& stream, const BigInt& big)
{
	return stream << big.ToString();
}


std::string BigInt::ToString() const 
{
	std::string serialized;
	for (auto it = _data.begin(); it != _data.end(); it++)
	{
		serialized.insert(0, std::to_string(*it));
	}

	if (_sign)
	{
		serialized.insert(0, "-");
	}

	return serialized;
}


BigInt::~BigInt() {}
