#include "gtest/gtest.h"
#include "gauss.h"
#include <fstream>
#include <vector>
#include <iostream>

TEST(Gauss, getMatrix)
{
    int a = 3, b = 4;
    std::vector<std::vector<double>> m0 = createFile("test_getMatrix.csv", a, b);
    std::vector<std::vector<double>> m1 = getMatrix("test_getMatrix.csv");

    for(int i = 0; i < a; i++)
        for(int j = 0; j < b; j++)
            EXPECT_NEAR(m0[i][j], m1[i][j], 0.01);
}

TEST(GaussMethodTest, ConvertsToUpperTriangular) 
{
    std::vector<std::vector<double>> matrix = 
    {
        {2, 1, -1},
        {-3, -1, 2},
        {-2, 1, 2}
    };

    std::vector<std::vector<double>> result = gaussMethod(matrix);

    EXPECT_EQ(result[1][0], 0.0);
    EXPECT_EQ(result[2][0], 0.0);
    EXPECT_EQ(result[2][1], 0.0);

    EXPECT_EQ(result[0][0], 1.0);
    EXPECT_EQ(result[1][1], 1.0);
}

TEST(FundSolutionTest, FundamentalSolution) 
{
    std::vector<std::vector<double>> upperTriangular = 
    {
        {1, 0, -2, 3},
        {0, 1, 1, -1}
    };

    std::vector<std::vector<double>> result = fundSolution(upperTriangular);

    ASSERT_EQ(result.size(), 2);
    ASSERT_EQ(result[0].size(), 4);

    EXPECT_EQ(result[0][2], 1.0);
    EXPECT_EQ(result[1][3], 1.0);
}

TEST(FundSolutionTest, NoFreeVariables) 
{
    std::vector<std::vector<double>> matrix = 
    {
        {1, 0, 0},
        {0, 1, 0},
        {0, 0, 1}
    };

    std::vector<std::vector<double>> result = fundSolution(matrix);

    EXPECT_TRUE(result.empty());
}

TEST(AllFunctions, RandomInput)
{
    for(int i = 1; i <= 15; i+=5)
    {
        int a = 10 * i, b = 12 * i;
        createFile("test_getMatrix.csv", a, b);
        std::vector<std::vector<double>> m = getMatrix("test_getMatrix.csv");
        std::vector<std::vector<double>> s = fundSolution(gaussMethod(m));

        for(int i = 0; i < s.size(); i < 0)
        {
            for(int j = 0; j < m.size(); j++)
            {
                double sum = 0;
                for(int l = 0; l < s[0].size(); l++)
                {
                    sum += m[j][l] * s[i][l];
                }
                EXPECT_NEAR(sum, 0, 2e-10);
            }
        }
        /*for(int j = 0; j < m[0].size(); j++)
        {
        std::cout<<"test "<<j<<std::endl;
            for(int k = 0; k < s.size(); k++)
            {
                double a = 0;
                for(int l = 0; l < s[0].size(); l++)
                {
                    a += m[k][l] * s[k][l];
                }
                EXPECT_NEAR(a, 0, 2e-10);
            }
        }*/
    }
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}