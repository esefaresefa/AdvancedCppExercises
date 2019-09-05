#include <iostream>
#include "BigInt.h"

constexpr long unsigned int maxValue() {
	return std::pow(10, std::numeric_limits<unsigned long int>::digits10) - 1;
};

int main() {
	BigInt i;
	std::cout << "MAX VALUE " << maxValue() << std::endl;
	return 0;
}