#include <iostream>
#include <string>
#include <cassert>
#include "BigInt.h"


int main() 
{
	std::cout << "MAX BLOCK VALUE: " << BigInt::MaxBlockValue() << std::endl;
	std::cout << "MAX NUMBER OF DIGITS PER BLOCK: " << BigInt::MaxBlockDigits() << std::endl << std::endl;

	try 
	{

// Constructors
		std::string test1("-5146513549846549864646546468448");
		BigInt big_1 = test1;
		std::cout	<< "Constructor - BigInt(const std::string& value) : " << std::endl 
					<< test1 << std::endl << "=" << std::endl << big_1.ToString() << std::endl << std::endl;
		assert(big_1.ToString() == test1);


		int test2(1234567890);
		BigInt big_2 = test2;
		std::cout << "Constructor - BigInt(const int& integer) : " << std::endl
			<< big_2.ToString() << std::endl << "=" << std::endl << test2 << std::endl << std::endl;
		assert(big_2 == test2);


		uint64_t test2a(12345678901234567890);
		BigInt big_2a = test2a;
		std::cout << "Constructor - BigInt(const uint64_t& integer) : " << std::endl
			<< big_2a.ToString() << std::endl << "=" << std::endl << test2a << std::endl << std::endl;
		assert(big_2a == test2a);


		// Copy constructors
		BigInt big_3(big_1);
		std::cout	<< "Copy constructor - BigIng(const BigInt& other) : " << std::endl 
					<< big_1.ToString() << std::endl << "=" << std::endl << big_3.ToString() << std::endl << std::endl;
		assert(big_1.ToString() == big_3.ToString());


		long long test4 = -3467455346373472;
		BigInt big_4 = -3467455346373472;
		std::cout << "Copy assignment - BigInt = long long : " << std::endl
			<< big_4.ToString() << std::endl << "=" << std::endl << test4 << std::endl << std::endl;
		assert(big_4 == test4);




// Operations

		// Addition
		BigInt big_10 = "999999999";
		big_10 += 101;
		std::cout << "Operator+= : 999999999 += 101" << " == " << big_10 << std::endl << std::endl;
		assert(big_10.ToString() == "1000000100");


		BigInt big_10a = "-100";
		big_10a += 101;
		std::cout << "Operator+= : -100 += 101" << " == " << big_10a << std::endl << std::endl;
		assert(big_10a.ToString() == "1");


		BigInt big_11 = "999999999";
		big_11++;
		std::cout << "Operator++ : 999999999++" << " == " << big_11 << std::endl << std::endl;
		assert(big_11.ToString() == "1000000000");


		// Subtraction
		BigInt big_12 = "1000000100";
		big_12 -= 101;
		std::cout << "Operator-= : 1000000100 -= 101" << " == " << big_12 << std::endl << std::endl;
		assert(big_12.ToString() == "999999999");


		BigInt big_8 = big_2 - big_2;
		std::cout << "Operator - : 1234567890 - 1234567890 " << " == " << big_8 << std::endl << std::endl;
		std::string test5 = "0";
		assert(big_8.ToString() == test5);


		BigInt big_13 = "1000000000";
		big_13--;
		std::cout << "Operator-- : 1000000000--" << " == " << big_13 << std::endl << std::endl;
		assert(big_13.ToString() == "999999999");


		// Multiplication
		BigInt big_6 = BigInt("999999999999999999")*BigInt("999999999999999999");
		std::cout << "Operator * : 999999999999999999 * 999999999999999999" << " == " << big_6 << std::endl << std::endl;
		std::string test6 = "999999999999999998000000000000000001";
		assert(big_6.ToString() == test6);


		std::cout << "MUL BY ZERO" << std::endl;
		BigInt big_6a = BigInt("987654321")*BigInt("0");
		std::cout << "Operator * : 987654321 * 0" << " == " << big_6a << std::endl << std::endl;
		std::string test6a = "0";
		assert(big_6a.ToString() == test6a);


		// Division
		int divisor = 9;
		BigInt big_7 = BigInt("9999999999") / divisor;
		std::cout << "Operator / : 9999999999 / 9" << " == " << ((divisor != 0) ? big_7.ToString() : "Division by zero is impossible!") << std::endl << std::endl;
		std::string test7 = "1111111111";
		assert(big_7.ToString() == test7);


		std::cout << "DIV BY ZERO" << std::endl;
		divisor = 0;
		BigInt big_7a = BigInt("9999999999") / divisor;
		std::cout << "Operator / : 9999999999 / 0" << " == " << ((divisor != 0) ? big_7a.ToString() : "Division by zero is impossible!") << std::endl << std::endl;
		std::string test7a = "9999999999";
		assert(big_7a.ToString() == test7a);


		BigInt big_14 = 133 % BigInt(10);
		std::cout << "Operator % : 133 % 10" << " == " << big_14 << std::endl << std::endl;
		std::string test14 = "3";
		assert(big_14.ToString() == test14);


		BigInt big_15 = 2465423774;
		BigInt big_15a = 1005894093;
		bool minor = big_15 >= big_15a;
		std::cout << "Operator <= : 2465423774 >= 1005894093" << " == " << ((minor) ? "TRUE" : "FALSE") << std::endl << std::endl;
		assert(minor == true);


		// Power
		std::cout << "POW:" << std::endl;
		BigInt big_16 = 10000;
		BigInt big_16a = pow(big_16, 10);
		std::cout << "Pow(10000, 10)" << " == " << big_16a << std::endl << std::endl;
		std::string test16 = "10000000000000000000000000000000000000000";
		assert(big_16a.ToString() == test16);


		std::cout << "POW BY ZERO:" << std::endl;
		BigInt big_17 = 100;
		BigInt big_17a = pow(big_17, 0);
		std::cout << "Pow(100, 0)" << " == " << big_17a << std::endl << std::endl;
		std::string test17 = "1";
		assert(big_17a.ToString() == test17);



		//BigInt big_15 = 7;
		//big_15 &= BigInt(0);
		//std::cout << "Operator & : " << big_15 << "" << std::endl;
		//assert(big_15 == 0);


		/*BigInt big_15a = big_2 & BigInt("5555555555");
		std::cout << "Operator & : " << big_15a << " == " << "1224868034" << std::endl;
		std::string test15 = "1224868034";
		assert(big_15a.ToString() == test15);


		BigInt big_16 = big_2 | BigInt("5555555555");
		std::cout << "Operator ! : " << big_16 << " == " << "5565255411" << std::endl;
		std::string test16 = "5565255411";
		assert(big_16.ToString() == test16);


		BigInt big_17 = big_2 ^ BigInt("5555555555");
		std::cout << "Operator ^ : " << big_17 << " == " << "1753946161" << std::endl;
		std::string test17 = "1753946161";
		assert(big_17.ToString() == test17);


		BigInt big_4(1);
		big_4 <<= 4;
		std::cout << "Left shift operator : " << big_4 << " == " << 16 << std::endl;
		assert(big_4 == 16);*/
	}
	catch (std::runtime_error e)
	{
		std::cout << e.what() << std::endl;
	}

	char end;
	std::cout << std::endl << "Press any char and ENTER to quit :";
	std::cin >> end;

	return 0;
}