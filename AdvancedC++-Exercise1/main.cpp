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
		std::cout	<< "Constructor - BigIng(const std::string& value)" << std::endl 
					<< test1 << std::endl << "=" << std::endl << big_1.ToString() << std::endl << std::endl;
		assert(test1 == big_1.ToString());
		


		std::string test2 = "-1234567890";
		BigInt big_2(test2);
		std::cout << "Constructor - BigIng(const std::string& value)" << std::endl
			<< big_2.ToString() << std::endl << "=" << std::endl << test2 << std::endl << std::endl;
		assert(big_2.ToString() == test2);



		BigInt big_3(big_1);
		std::cout	<< "Copy constructor - BigIng(const BigInt& other)" << std::endl 
					<< big_1.ToString() << std::endl << "=" << std::endl << big_3.ToString() << std::endl << std::endl;
		assert(big_1.ToString() == big_3.ToString());


		BigInt big_6 = BigInt("999999999999999999")*BigInt("999999999999999999");
		std::cout << "* operator - " << big_6 << " = " << "999999999999999998000000000000000001" << std::endl;
		std::string test3 = "999999999999999998000000000000000001";
		assert(big_6.ToString() == test3);

		bool minor = big_2<= big_2;
		std::cout << "<= operator - " << minor << " = " << "true" << std::endl;
		assert(minor == true);

		BigInt big_8 = big_2 - big_2;
		std::cout << "- operator - " << big_8 << " = " << "0" << std::endl;
		std::string test5 = "0";
		assert(big_8.ToString() == test5);

		BigInt big_7= big_2 / BigInt("-1234567890");
		std::cout << "/ operator - " << big_7 << " = " << "1" << std::endl;
		std::string test4 = "1";
		assert(big_7.ToString() == test4);

		BigInt big_4(1);
		big_4 <<= 4;
		std::cout << "Left shift operator - " << big_4 << " = " << 16 << std::endl;
		assert(big_4 == 16);

		BigInt big_5(1);
		size_t max = BigInt::MaxBitPerBlock();
		big_5 <<= max;
		std::cout << "Left shift operator - " << big_5 << " = " << 1000000000 << std::endl;
		assert(big_5 == BigInt("1000000000"));
	}
	catch (std::runtime_error e)
	{
		std::cout << e.what() << std::endl;
	}

	return 0;
}