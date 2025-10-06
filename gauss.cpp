#include "gauss.h"
#include <iostream>

std::vector<std::vector<double>> getMatrix(std::string fileName)
{
    lazycsv::parser<lazycsv::mmap_source, lazycsv::has_header<false>> file(fileName);
    std::vector<std::vector<double>> matrix;
    for(auto i : file)
    {
        std::vector<double> line;
        for(auto j : i)
        {
            std::string val = std::string(j.trimmed());
            line.push_back(std::stod(val));
        }
        matrix.push_back(line);
    }
    return matrix;
}
std::vector<std::vector<double>> createFile(std::string fileName, int a, int b)
{
    std::random_device d;
    std::mt19937 gen(d());
    std::uniform_real_distribution<> dist(0.0, 1000.0);

    std::vector<std::vector<double>> m(a, std::vector<double>(b));
    for(int i = 0; i < a; i++)
    {
        for(int j = 0; j < b; j++)
        {
            m[i][j] = dist(gen);
        }
    }


    std::ofstream file(fileName, std::ios::trunc);
    for(int i = 0; i < m.size(); i++)
    {
        for(int j = 0; j < m[0].size(); j++)
        {
            file << m[i][j];
            if(j + 1 != m[0].size())
                file << ", ";
        }
        if(i + 1 != m.size())
            file << "\n";
    }
    file.close();
    return m;
}

void writeAnswear(std::string fileName, std::vector<std::vector<double>> solution)
{
    std::ofstream file(fileName, std::ios::trunc);
    for(int i = 0; i < solution.size(); i++)
    {
        for(int j = 0; j < solution[0].size(); j++)
        {
            file << solution[i][j];
            if(j + 1 != solution[0].size())
                file << ", ";
        }
        if(i + 1 != solution.size())
            file << "\n";
    }
    file.close();
}

std::vector<std::vector<double>> gaussMethod(std::vector<std::vector<double>> matrix)
{
    int colOfZeroes = 0;
    int j = 0;
    for(int i = 0; i < matrix[0].size(); i++)
    {
        bool allZeroes = false;
        j = i - colOfZeroes;
        
        while(matrix[j][i] == 0 )
        {
            j++;
            if(j == matrix.size())
            {
                allZeroes = true;
                break;
            }
        }
        if(!allZeroes)
        {              
            std::swap(matrix[i - colOfZeroes], matrix[j]);
            for(int l = i - colOfZeroes + 1; l < matrix.size(); l++)
            {
                lineDiff(matrix, i - colOfZeroes, l, i);
            }
            for(int l = 0; l < i - colOfZeroes; l++)
            {
                lineDiff(matrix, i - colOfZeroes, l, i);
            }
        }
        else
            colOfZeroes++;

        if(j == matrix.size() - 1)
            break;
    }
    devideLines(matrix);
    return matrix;
}

std::vector<std::vector<double>> fundSolution(std::vector<std::vector<double>> matrix)
{
    std::set<int> index; 
    int main;
    for(int i = 0; i < matrix.size(); i++)
    {
        main = false;
        for(int j = 0; j < matrix[0].size(); j++)
        {
            if(matrix[i][j] == 1 && !main)
                main = true;
            else if(matrix[i][j] != 0)
                index.insert(j);
        }
    }

    std::vector<std::vector<double>> solution(index.size(), std::vector<double>(matrix[0].size()));

    int ind = 0;
    int indJ;
    for(auto i : index)
    {
        indJ = 0;
        for(int j = 0; j < solution[0].size(); j++)
        {
            if(index.find(j) != index.end())
            {
                if(j == i)
                    solution[ind][j] = 1;
                else 
                    solution[ind][j] = 0;
            }
            else
            {
                solution[ind][j] = matrix[indJ][i] * -1;
                indJ++;
            }
        }
        ind++;
    }
    return solution;
}

void lineDiff(std::vector<std::vector<double>>& matrix, int lineI, int lineJ, int k)
{
    double koefJ = matrix[lineJ][k];
    double koefI = matrix[lineI][k];
    for(int i = 0; i < matrix[lineI].size(); i++)
        matrix[lineJ][i] -= matrix[lineI][i] / koefI * koefJ;
}

void devideLines(std::vector<std::vector<double>>& matrix)
{
    double firstInLine;
    for(int i = 0; i < matrix.size(); i++)
    {
        firstInLine = 0;
        for(int j = 0; j < matrix[0].size(); j++)
        {
            if(matrix[i][j] != 0)
            {
                if(firstInLine == 0)
                {
                    firstInLine = matrix[i][j];
                }
                matrix[i][j] /= firstInLine;
            }
        }
    }
}