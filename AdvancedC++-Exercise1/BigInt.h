#pragma once

#include <vector>


class BigInt
{

public:

	BigInt();

	BigInt(int integer);

	BigInt(std::string value);

	BigInt& operator+= (const BigInt& other);

	BigInt& operator-= (const BigInt& other);

	BigInt operator- () const;

	BigInt& operator++ ();

	BigInt operator++ (int);

	BigInt& operator*= (const BigInt& other);

	BigInt& operator%= (const BigInt& other);

	BigInt& operator/= (const BigInt& other);

	BigInt& operator&= (const BigInt& other);

	BigInt& operator|= (const BigInt& other);

	BigInt& operator^= (const BigInt& other);

	BigInt operator<< (int steps) const;

	BigInt& operator<<= (int steps);

	BigInt operator>> (int steps) const;

	BigInt& operator>>= (int steps);

	BigInt Abs() const;

	bool operator== (const BigInt& other) const;

	bool operator> (const BigInt& other) const;

	bool operator>= (const BigInt& other) const;

	bool operator< (const BigInt& other) const;

	bool operator<= (const BigInt& other) const;

	// BigInt to string
	std::string ToString() const;

	// operator std::string() const; // TODO

	// The maximum number of digits of a single block
	static size_t MaxBlockDigits();

	// The maximum value of a single block of digits
	static unsigned long MaxBlockValue();

	// The number of bits needed for rapresenting the MaxBlockValue
	static size_t MaxBitPerBlock();

	virtual ~BigInt();

protected:

	//true == -
	bool _sign;

	std::vector<unsigned long int> _data;

	int GetSign() const;

	void Trim();

	bool IsOnlyDigits(const std::string& value) const;
};


// Binary operators are typically implemented as non-members to maintain symmetry
// No need to access internal data so it's not friend function of BigInt
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
	lhs &= rhs;
	return lhs;
}


inline BigInt operator/ (BigInt lhs, const BigInt& rhs)
{
	lhs /= rhs;
	return lhs;
}

inline std::ostream& operator<< (std::ostream& stream, const BigInt& big)
{
	return stream << big.ToString();
}


inline BigInt pow(BigInt base, int exponent)
{
	BigInt returnValue;
	for (int i = 0; i < exponent; i++)
	{
		returnValue += base * base;
	}
	return returnValue;
}


inline BigInt pow(BigInt base, BigInt& exponent) 
{ 
	BigInt returnValue;
	for (BigInt i = 0; i < exponent; i++)
	{
		returnValue += base * base;
	}
	return base;
};


inline unsigned long BigInt::MaxBlockValue()
{
	double value = pow(10, std::numeric_limits<unsigned long int>::digits10);
	return (static_cast<unsigned long int>(value) - 1);
}


inline size_t BigInt::MaxBlockDigits()
{
	return std::numeric_limits<unsigned long int>::digits10;
}


inline size_t BigInt::MaxBitPerBlock()
{
	return static_cast<size_t>(std::log2(MaxBlockValue())) + 1;
}