#include <iostream>
#include <string>
#include "coder.h"

int main()
{
    std::string in;
    std::getline(std::cin, in);
    encode(in, std::cout);

    return 0;
}