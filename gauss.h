#include "lazycsv.hpp"
#include <vector>
#include <string>
#include <algorithm>
#include <random>
#include <fstream>
#include <set>
#include <iomanip>

std::vector<std::vector<double>> getMatrix(std::string fileName);
std::vector<std::vector<double>> createFile(std::string fileName, int a, int b);
void writeAnswear(std::string fileName, std::vector<std::vector<double>>);

std::vector<std::vector<double>> fundSolution(std::vector<std::vector<double>> matrix);

std::vector<std::vector<double>> gaussMethod(std::vector<std::vector<double>> matrix);

void lineDiff(std::vector<std::vector<double>>& matrix, int lineI, int lineJ, int k);
void devideLines(std::vector<std::vector<double>>& matrix);