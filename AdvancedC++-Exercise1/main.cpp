#include <iostream>
#include <string>
#include <cassert>
#include "BigInt.h"


int main() 
{
	std::cout << "MAX BLOCK VALUE " << BigInt::MaxBlockValue() << std::endl;
	std::cout << "MAX NUMBER OF DIGITS PER BLOCK " << BigInt::MaxBlockDigits() << std::endl << std::endl;

	try 
	{
		std::string test1 = "-5146513549846549864646546468448";
		
		BigInt big_1(test1);
		std::cout << "Constructor - BigIng(const std::string& value)" << std::endl << test1 << std::endl << "=" << std::endl << big_1.ToString() << std::endl << std::endl;
		assert(test1 == big_1.ToString(), "Constructor with string has failed");
		
		BigInt big_2(big_1);
		std::cout << "Copy constructor - BigIng(const BigInt& other)" << std::endl << big_1.ToString() << std::endl << "=" << std::endl << big_2.ToString() << std::endl << std::endl;
		assert(big_1.ToString() == big_2.ToString(), "Copy constructor has failed");
	}
	catch (std::runtime_error e)
	{
		std::cout << e.what() << std::endl;
	}

	return 0;
}