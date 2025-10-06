#ifndef CODER_H
#define CODER_H

#include <iostream>
#include <string>
#include <math.h>

void encode(std::string& input, std::basic_ostream<char>& output);
int decode(std::string& input, std::basic_ostream<char>& output);

#endif