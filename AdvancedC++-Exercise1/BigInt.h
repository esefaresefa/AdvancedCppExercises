#pragma once

#include <vector>


class BigInt
{

public:

	BigInt(int integer);

	BigInt();

	BigInt operator* (const BigInt& other);

	BigInt Power(BigInt base, int exponent);
	
	BigInt(const std::string& value);

	// The maximum number of digits of a single block
	static int MaxBlockDigits();

	// The maximum value of a single block of digits
	static unsigned long MaxBlockValue();

	// BigInt to string
	std::string ToString() const;
	// operator std::string() const; // TODO

	BigInt& operator= (const BigInt& other);

	BigInt& operator+= (const BigInt& other);

	BigInt& operator% (const BigInt& other);

	BigInt& operator/ (const BigInt& other);

	BigInt& operator%= (const BigInt& other);

	BigInt& operator/= (const BigInt& other);


	BigInt& operator-= (const BigInt& other);

	BigInt operator- () const;

	BigInt& operator++ ();
	BigInt operator++ (int);
	//da definire
	bool operator== (const BigInt& other)const;
	bool operator> (const BigInt& other)const;
	bool operator< (const BigInt& other)const;
	bool operator>= (const BigInt& other)const;
	bool operator<= (const BigInt& other)const;

	BigInt& operator&= (const BigInt& other);

	BigInt& operator|= (const BigInt& other);

	BigInt& operator^= (const BigInt& other);

	virtual ~BigInt();

protected:

	//true == -
	bool _sign;

	std::vector<unsigned long int> _data;

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


inline std::ostream& operator<< (std::ostream& stream, const BigInt& big)
{
	return stream << big.ToString();
}


inline unsigned long BigInt::MaxBlockValue()
{
	double value = pow(10, std::numeric_limits<unsigned long int>::digits10);
	return (static_cast<unsigned long int>(value) - 1);
}


inline int BigInt::MaxBlockDigits()
{
	return std::numeric_limits<unsigned long int>::digits10;
}
