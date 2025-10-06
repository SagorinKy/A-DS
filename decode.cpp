#include <iostream>
#include <string>
#include "coder.h"

int main()
{
    std::string in;
    std::getline(std::cin, in);
    if (decode(in, std::cout) == 1)
        return 1;
    return 0;
}