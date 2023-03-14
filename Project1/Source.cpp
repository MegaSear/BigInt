#include "BigInt.h"
#include <iostream>
	
int main()
{
	std::string a = "-1";
	BigInt a_big(a);
	std::string b = "6";
	BigInt b_big(b);
	std::cout << (~a_big) << std::endl;
	std::cout << (~-1) << std::endl;
	return 0;
}