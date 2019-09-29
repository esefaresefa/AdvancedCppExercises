#pragma once

#include <deque>
#include <string>
#include <utility>

class BigInt
{

public:

	// Constructors
	BigInt();
	
	BigInt(const BigInt& other);
	
	BigInt(const int& integer);

	BigInt(const uint32_t& integer);

	BigInt(const long& value);

	BigInt(const unsigned long& value);

	BigInt(const long long& value);

	BigInt(const uint64_t& integer);

	BigInt(const char* literals);

	BigInt(const std::string& literals);


	// Copy operators
	BigInt& operator=(const BigInt& other);
	BigInt& operator=(const int& integer);
	BigInt& operator=(const uint32_t& integer);
	BigInt& operator=(const long& value);
	BigInt& operator=(const unsigned long& value);
	BigInt& operator=(const long long& value);
	BigInt& operator=(const uint64_t& value);
	BigInt& operator=(const std::string& literals);


	// Sum
	BigInt& operator+= (const BigInt& other);


	// Subtraction
	BigInt& operator-= (const BigInt& other);


	// Multiplication
	BigInt& operator*= (const BigInt& other);
	BigInt& operator*=(const long long& value);


	// Division
	std::pair<BigInt,BigInt> DivMod(const BigInt Dividend, const BigInt Divisor);
	BigInt& operator/=(const BigInt& other);
	BigInt& operator%=(const BigInt& other);
	BigInt& operator/=(const long long& value);


	// Unary operators
	BigInt operator- () const;							// minus operator
	BigInt& operator-- ();								// prefix op --
	BigInt operator-- (const int);						// postfix op --
	BigInt& operator++();								// prefix op ++
	BigInt operator++(const int);						// postfix op ++

	// Compare
	int compare(BigInt const& other) const; //0 a == b, -1 a < b, 1 a > b

	bool operator==(const BigInt& other) const;
	bool operator!=(const BigInt& other) const;
	bool operator>(const BigInt& other) const;
	bool operator>=(const BigInt& other) const;
	bool operator<(const BigInt& other) const;
	bool operator<=(const BigInt& other) const;

	// Bitwise operators
	BigInt& operator&= (const BigInt& other);

	BigInt& operator|= (const BigInt& other);

	BigInt& operator^= (const BigInt& other);

	BigInt operator<< (int steps) const;

	BigInt& operator<<= (int steps);

	BigInt operator>> (int steps) const;

	BigInt& operator>>= (int steps);


// Utils

	// Absolute value of BigInt
	BigInt Abs() const;

	// BigInt to string
	std::string ToString() const;

	// The maximum number of digits of a single block
	static size_t MaxBlockDigits();

	// The maximum value of a single block of digits
	static unsigned long MaxBlockValue();

	// The number of bits needed for rapresenting the MaxBlockValue
	static size_t MaxBitPerBlock();

	// Utilities
	void clear();

	virtual ~BigInt();

protected:

	//true == -
	bool _sign;

	std::deque<uint32_t> _data;

	int GetSign() const;

	void Trim();

	bool IsOnlyDigits(const std::string& value) const;
};


// Binary operators are typically implemented as non-members to maintain symmetry
// No need to access internal data so it's not friend function of BigInt
//BigInt
inline BigInt operator+ (BigInt lhs, const BigInt& rhs)
{
	lhs += rhs;
	return lhs;
}


inline BigInt operator- (BigInt lhs, const BigInt& rhs)
{
	lhs -= rhs;
	return lhs;
}


inline BigInt operator* (BigInt lhs, const BigInt& rhs)
{
	lhs *= rhs;
	return lhs;
}


inline BigInt operator% (BigInt lhs, const BigInt& rhs)
{
	lhs %= rhs;
	return lhs;
}


inline BigInt operator/ (BigInt lhs, const BigInt& rhs)
{
	lhs /= rhs;
	return lhs;
}


// Bitwise op
inline BigInt operator& (BigInt lhs, const BigInt& rhs)
{
	lhs &= rhs;
	return lhs;
}


inline BigInt operator| (BigInt lhs, const BigInt& rhs)
{
	lhs |= rhs;
	return lhs;
}


inline BigInt operator^ (BigInt lhs, const BigInt& rhs)
{
	lhs ^= rhs;
	return lhs;
}

inline std::ostream& operator<< (std::ostream& stream, const BigInt& big)
{
	return stream << big.ToString();
}


// Power
inline BigInt pow(BigInt& base, int exponent)
{
	BigInt returnValue = base;

	if (exponent == 0)
		return 1;

	if (exponent == 1)
		return returnValue;

	else
	{
		return returnValue * pow(base, --exponent);
	}
}


inline BigInt pow(BigInt& base, BigInt& exponent)
{
	BigInt returnValue = base;

	if (exponent == 0)
		return 1;

	if (exponent == 1)
		return returnValue;

	else
	{
		return returnValue * pow(base, --exponent);
	}
};


inline unsigned long BigInt::MaxBlockValue()
{
	double value = pow(10, std::numeric_limits<uint32_t>::digits10);
	return (static_cast<uint32_t>(value) - 1);
}


inline size_t BigInt::MaxBlockDigits()
{
	return std::numeric_limits<uint32_t>::digits10;
}


inline size_t BigInt::MaxBitPerBlock()
{
	return static_cast<size_t>(std::log2(MaxBlockValue())) + 1;
}