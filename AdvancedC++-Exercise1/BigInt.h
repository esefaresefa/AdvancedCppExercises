#pragma once

#include <vector>


class BigInt
{

public:
	
	BigInt();
	
	BigInt(const std::string& value);

	// The maximum number of digits of a single block
	static int MaxBlockDigits();

	// The maximum value of a single block of digits
	static unsigned long long MaxBlockValue();

	// BigInt to string
	std::string ToString() const;

	// Output stream operator
	friend std::ostream& operator<< (std::ostream& stream, const BigInt& matrix);

	BigInt operator+ (const BigInt& other);

	virtual ~BigInt();

protected:

	bool _sign;

	std::vector<unsigned long long int> _data;

	bool IsOnlyDigits(const std::string& value) const;

	unsigned long long int Carry(unsigned long long int a, unsigned long long int b) const;
};


inline unsigned long long BigInt::MaxBlockValue()
{
	double value = pow(10, std::numeric_limits<unsigned long long int>::digits10);
	return (value - 1);
}


inline int BigInt::MaxBlockDigits()
{
	return std::numeric_limits<unsigned long long int>::digits10;
}
