#include <iostream>
#include <sstream>
#include <cassert>
#include "BigInt.h"


int main() 
{
	std::cout << "MAX BLOCK VALUE " << BigInt::MaxBlockValue() << std::endl;
	std::cout << "MAX NUMBER OF DIGITS PER BLOCK " << BigInt::MaxBlockDigits() << std::endl;

	try 
	{
		std::string test1 = "-5146513549846549864646546468448";
		BigInt big_1(test1);

		assert(test1 == big_1.ToString(), "Constructor with string failed");
		std::cout << test1 << std::endl << big_1.ToString() << std::endl;
	}
	catch (std::runtime_error e)
	{
		std::cout << e.what() << std::endl;
	}

	return 0;
}