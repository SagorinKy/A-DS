#include "gauss.h"
#include <iostream>
#include <iomanip>
#include <vector>

int main()
{
    int a = 300, b = 400;
    createFile("main.csv", a, b);
    std::vector<std::vector<double>> m = getMatrix("main.csv");
    /*std::vector<std::vector<double>> m = 
    {
        {1, 1, 4, 8},
        {0, 0, 2, 5},
        {0, 0, 2, 5}
    };*/
    m = gaussMethod(m);
    
    for(int i = 0; i < m.size(); i++)
    {
        for(int j = 0; j < m[0].size(); j++)
        {
            std::cout << std::setw(12) << m[i][j] << " ";
        }
        std::cout<<"\n";
    }
    std::cout<<"\n";
    std::cout<<"\n";
    std::vector<std::vector<double>> s = fundSolution(m);

    for(int i = 0; i < s.size(); i++)
    {
        for(int j = 0; j < s[0].size(); j++)
        {
            std::cout << std::setw(12) << s[i][j] << " ";
        }
        std::cout<<"\n";
    }
    return 0;
}