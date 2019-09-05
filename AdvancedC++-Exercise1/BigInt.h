#pragma once
#include <vector>
#include <limits>


class BigInt
{
public:
	BigInt();
	BigInt(const std::string& value);
	virtual ~BigInt();
private:
	bool m_sign;
	std::vector<unsigned long int> m_data;
};

