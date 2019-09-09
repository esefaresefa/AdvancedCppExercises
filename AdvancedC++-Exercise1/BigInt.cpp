#include "BigInt.h"
#include <iostream>
#include <string>
#include <limits>
#include <algorithm>


BigInt::BigInt() {}


BigInt::BigInt(const std::string& literals) throw(std::runtime_error)
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
}


bool BigInt::IsOnlyDigits(const std::string& value) const
{
	std::string::const_iterator it = value.begin();
	if (*it == '-') {
		it++;
	}
	return std::all_of(it, value.end(), ::isdigit);
}


std::ostream& operator<< (std::ostream& stream, const BigInt& big)
{
	return stream << big.ToString();
}


std::string BigInt::ToString() const 
{
	std::string serialized;
	if (_sign)
	{
		serialized += "-";
	}
	for (auto it = _data.begin(); it != _data.end(); it++)
	{
		serialized += std::to_string(*it);
	}
	return serialized;
}


BigInt::~BigInt()
{
}
