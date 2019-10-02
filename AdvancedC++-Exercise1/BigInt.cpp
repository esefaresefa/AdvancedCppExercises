#include "BigInt.h"
#include <iostream>
#include <sstream>
#include <string>
#include <limits>
#include <algorithm>


BigInt::BigInt() {}


BigInt::BigInt(const int& integer)
{
	*this = integer;
}

BigInt::BigInt(const uint32_t& integer)
{
	*this = integer;
}


BigInt::BigInt(const long& value)
{
	*this = value;
}

BigInt::BigInt(const unsigned long & value)
{
	*this = value;
}


BigInt::BigInt(const long long& value)
{
	*this = value;
}

BigInt::BigInt(const uint64_t& value)
{
	*this = value;
}

BigInt::BigInt(const char * literals)
	: BigInt(std::string(literals))
{
}


BigInt::BigInt(const BigInt& other)
{
	*this = other;
}


BigInt::BigInt(const std::string& literals)
{
	if (!IsOnlyDigits(literals) && literals.size()>1 && !IsOnlyDigits(literals.substr(1, literals.size())))
	{
		throw std::runtime_error("String is not a _data");
	}

	size_t maxBlockDigits = MaxBlockDigits();

	int first = literals.size() - maxBlockDigits;
	int last = 0;
	if (literals[0] == '-')
	{
		_sign = true;
		last = 1;
	}
	else
	{
		_sign = false;
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


// Copy operators
BigInt& BigInt::operator=(const BigInt& other)
{
	_data.clear();

	_sign = other._sign;
	_data = other._data;

	return *this;
}

BigInt& BigInt::operator=(const int& integer)
{
	_data.clear();

	std::stringstream ss;
	ss << integer;
	std::string s;
	ss >> s;

	return *this = s;
}

BigInt & BigInt::operator=(const uint32_t& integer)
{
	_data.clear();

	std::stringstream ss;
	ss << integer;
	std::string s;
	ss >> s;

	return *this = s;
}

BigInt& BigInt::operator=(const long& value)
{
	_data.clear();

	std::stringstream ss;
	ss << value;
	std::string s;
	ss >> s;

	return *this = s;
}

BigInt & BigInt::operator=(const unsigned long & value)
{
	_data.clear();

	std::stringstream ss;
	ss << value;
	std::string s;
	ss >> s;

	return *this = s;
}

BigInt& BigInt::operator=(const long long& value)
{
	_data.clear();

	std::stringstream ss;
	ss << value;
	std::string s;
	ss >> s;

	return *this = s;
}

BigInt & BigInt::operator=(const uint64_t& value)
{
	_data.clear();

	std::stringstream ss;
	ss << value;
	std::string s;
	ss >> s;

	return *this = s;
}


BigInt& BigInt::operator=(const std::string& literals)
{
	int size = literals.length();

	(literals[0] == '-') ? _sign = true : _sign = false;

	while (true) {
		if (size <= 0)
			break;
		if (_sign && size <= 1)
			break;

		int length = 0;
		int num = 0;
		int prefix = 1;
		for (int i = size - 1; i >= 0 && i >= size - 9; i--)
		{
			if (literals[i] < '0' || literals[i] > '9')
				break;
			num += (literals[i] - '0') * prefix;
			prefix *= 10;
			length++;
		}
		_data.push_back(num);
		size -= length;
	}

	return *this;
}


// Sum
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
		*this -= (-other);
	}
	return *this;
}


// Subtraction
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


// Multiplication
BigInt& BigInt::operator*= (const BigInt & other)
{
	if (*this == 0 || other == 0)
		return *this = 0;

	BigInt first = *this;
	_sign = first._sign ^ other._sign;
	_data.clear();
	_data.resize(first._data.size() + other._data.size() - 1, 0);
	for (int i = 0; i < first._data.size(); i++)
	{
		for (int j = 0; j < other._data.size(); j++) {
			unsigned long long int aux = static_cast<unsigned long long int>(first._data[i]) * static_cast<unsigned long long int>(other._data[j]);
			aux += _data[i + j];
			if (aux <= MaxBlockValue())
			{
				_data[i + j] = static_cast<uint32_t>(aux);
			}
			else
			{
				_data[i + j] = aux % (MaxBlockValue() + 1);
				if (_data.size() > i + j + 1)
				{
					_data[i + j + 1] += aux / (MaxBlockValue() + 1); //carry
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


BigInt& BigInt::operator*=(const long long& value)
{
	BigInt temp(value);
	*this *= value;

	return *this;
}


// Division
std::pair<BigInt, BigInt> BigInt::DivMod(const BigInt Dividend, const BigInt Divisor)
{
	if (Dividend == 0 || Divisor == 0)
		return std::pair<BigInt, BigInt>(Dividend, Divisor);

	BigInt dividend = Dividend.Abs();
	BigInt divisor = Divisor.Abs();
	BigInt quotient;
	BigInt remainder;
	bool first = true;
	if (dividend >= divisor)
	{
		if (divisor == 0) {

		}
		remainder._data.resize(divisor._data.size());
		for (int i = dividend._data.size() - divisor._data.size(); i < dividend._data.size(); i++)
		{
			remainder._data[i - (dividend._data.size() - divisor._data.size())] = dividend._data[i];
		}
		for (int i = dividend._data.size() - divisor._data.size(); i >= 0; i--)
		{
			if (remainder < divisor)
			{
				quotient._data.insert(quotient._data.begin(), 0);
			}
			else
			{
				if (remainder == divisor)
				{
					quotient._data.insert(quotient._data.begin(), 1);
					remainder -= divisor;
				}
				else
				{
					int remainder2H;

					if (remainder._data.size() > 1 && !first)
					{
						remainder2H = remainder._data[remainder._data.size() - 1] * (MaxBlockValue() + 1) + remainder._data[remainder._data.size() - 2];
					}
					else
					{
						remainder2H = remainder._data[remainder._data.size() - 1];
						first = false;
					}
					int divisor1H = divisor._data[divisor._data.size() - 1];

					int minQuotient = remainder2H / (divisor1H + 1);
					int maxQuotient = fmin(remainder2H / divisor1H , pow(2,32)-1);
					int triedQuotient = (minQuotient + maxQuotient) / 2;
					while (!(remainder <= divisor * (triedQuotient + 1) && remainder >= divisor * triedQuotient))
					{
						if (remainder < divisor * (triedQuotient + 1))
						{
							maxQuotient = triedQuotient;
							if (triedQuotient != (minQuotient + maxQuotient) / 2)
							{
								triedQuotient = (minQuotient + maxQuotient) / 2;
							}
							else
							{
								triedQuotient--;
							}
						}
						else
						{
							minQuotient = triedQuotient;
							if (triedQuotient != (minQuotient + maxQuotient) / 2)
							{
								triedQuotient = (minQuotient + maxQuotient) / 2;
							}
							else
							{
								triedQuotient++;
							}
						}
					}
					if (remainder >= divisor * (triedQuotient + 1))
					{
						triedQuotient++;
					}
					quotient._data.insert(quotient._data.begin(), triedQuotient);
					remainder -= divisor * triedQuotient;
				}
			}
			if (i - 1 >= 0)
			{
				remainder._data.insert(remainder._data.begin(), dividend._data[i - 1]);
				if (remainder._data[remainder._data.size() - 1] == 0)
				{
					remainder._data.pop_back();
				}
			}
		}
	}
	else
	{
		quotient = 0;
		remainder = dividend;
	}
	quotient._sign = Dividend._sign ^ Divisor._sign;
	return std::pair<BigInt, BigInt>(quotient, remainder);
}


BigInt& BigInt::operator/= (const BigInt& other)
{
	std::pair<BigInt, BigInt> result = DivMod(*this, other);
	*this = result.first;
	return *this;
}


BigInt& BigInt::operator%= (const BigInt& other)
{
	std::pair<BigInt, BigInt> result = DivMod(*this, other);
	*this = result.second;
	return *this;
}


BigInt& BigInt::operator/=(const long long& value)
{
	BigInt temp(value);
	std::pair<BigInt, BigInt> result = DivMod(*this, temp);
	*this = result.first;
	return *this;
}


// Unary operators
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


BigInt BigInt::operator++(const int)
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


// COMPARE
int BigInt::compare(const BigInt &other) const //0 this == _data || -1 this < _data || 1 this > _data
{
	if (_sign && !other._sign)
		return -1;
	if (!_sign && other._sign)
		return 1;

	int check = 1;
	if (_sign && other._sign)
		check = -1;

	if (_data.size() < other._data.size())
		return -1 * check;
	if (_data.size() > other._data.size())
		return check;
	for (size_t i = _data.size(); i > 0; --i) {
		if (_data[i - 1] < other._data[i - 1])
			return -1 * check;
		if (_data[i - 1] > other._data[i - 1])
			return check;
	}

	return 0; // ==
}


// BigInt
bool BigInt::operator==(const BigInt& other) const
{
	return compare(other) == 0;
}

bool BigInt::operator!=(const BigInt& other) const
{
	return !(*this == other);
}

bool BigInt::operator<(const BigInt& other) const
{
	return compare(other) == -1;
}

bool BigInt::operator<=(const BigInt& other) const
{
	int compared = compare(other);

	return compared == 0 || compared == -1;
}

bool BigInt::operator>(const BigInt& other) const
{
	return compare(other) == 1;
}

bool BigInt::operator>=(const BigInt&  other) const
{
	int compared = compare(other);

	return compared == 0 || compared == 1;
}


// OLD COMPARE METHODS
//bool BigInt::operator== (const BigInt & other) const
//{
//	return !(*this < other) && !(other < *this);
//}
//
//
//bool BigInt::operator!= (const BigInt & other) const
//{
//	return !(*this == other);
//}
//
//
//bool BigInt::operator> (const BigInt & other) const
//{
//	return other < *this;
//}
//
//
//bool BigInt::operator< (const BigInt & other) const
//{
//	if (_sign != other._sign)
//	{
//		return GetSign() < other.GetSign();
//	}
//
//	if (_data.size() != other._data.size())
//	{
//		return _data.size() * GetSign() < other._data.size() * other.GetSign();
//	}
//
//	for (int i = _data.size() - 1; i >= 0; i--)
//	{
//		if (_data[i] != other._data[i])
//		{
//			return _data[i] * GetSign() < other._data[i] * GetSign();
//		}
//	}
//
//	return false;
//}
//
//
//bool BigInt::operator>= (const BigInt & other) const
//{
//	return !(*this < other);
//}
//
//
//bool BigInt::operator<= (const BigInt & other) const
//{
//	return !(other < *this);
//}


// Bitwise operators
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


BigInt& BigInt::operator^= (const BigInt & other)
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

	// Add the _sign in top of the _data
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


// Utilities
void BigInt::clear()
{
	_data.clear();
	_sign = false;
}


BigInt::~BigInt() {}
