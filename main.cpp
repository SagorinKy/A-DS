#include <iostream>
#include <string>
#include "coder.h"

int main()
{
	std::string in;
	while(true)
	{
		std::getline(std::cin, in);
		if(in == "0")
			break;
		encode(in, std::cout);
		std::cout << std::endl;
		std::getline(std::cin, in);
		if(in == "0")
			break;
		decode(in, std::cout);
		std::cout << std::endl;
	}
	return 0;
}
