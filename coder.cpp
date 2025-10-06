#include "coder.h"
#include <cstdint>

void encode(std::string& input, std::basic_ostream<char>& output)
{
    for(int i = 0; input.size() > i + 3; i+=4)
    {
        uint32_t fourBites = 0;
        uint8_t bite = 0;
        for(int j = 0; j < 4; j++)
        {
            bite = static_cast<uint8_t>(input[i + j]);
            fourBites += bite * static_cast<int>(pow(2, 8 * (3 - j)));
        }
        for (int j = 4; j >= 0; j--)
        {
            output << static_cast<char>(fourBites / static_cast<int>(pow(85, j)) + 33);
            fourBites -= fourBites / static_cast<int>(pow(85, j)) * static_cast<int>(pow(85, j));
        }
    }
    if(input.size() % 4 != 0)
    {
        int i = (input.size() / 4) * 4;
        uint32_t lastBites = 0;
        uint8_t bite = 0;
        for(int j = 0; j < input.size() - i; j++)
        {
            bite = static_cast<uint8_t>(input[i + j]);
            lastBites += bite * static_cast<int>(pow(2, 8 * (3 - j)));
        }
        for (int j = 4; j > 3 - input.size() % 4; j--)
        {
            output << static_cast<char>(lastBites / static_cast<int>(pow(85, j)) + 33);
            lastBites -= lastBites / static_cast<int>(pow(85, j)) * static_cast<int>(pow(85, j));
        }
    }
}
int decode(std::string& input, std::basic_ostream<char>& output)
{
    uint32_t fourBites = 0;
    uint8_t bite = 0;
    for(int i = 0; input.size() > i + 4; i+=5)
    {
        fourBites = 0;
        for (int j = 4; j >= 0; j--)
        {
            fourBites += (static_cast<uint32_t>(input[i + (4 - j)]) - 33) * static_cast<uint32_t>(pow(85, j));
        }
        for (int j = 3; j >= 0; j--)
        {
            bite = 0;
            bite = fourBites / static_cast<uint32_t>(pow(2, j * 8));
            if(bite < 33 || bite > 127)
                return 1;
            fourBites -= bite * static_cast<uint32_t>(pow(2, j * 8));
            output << static_cast<char>(bite);
        }
    }
    if(input.size() % 5 != 0)
    {
        fourBites = 0;
        int excess = input.size() % 5;
        for(int i = 4; i >= 5 - excess; i--)
        {
            fourBites += static_cast<uint32_t>(input[input.size() - excess + 4 - i] - 33) * static_cast<uint32_t>(pow(85, i));
        }
        for(int i = 0; i < 5 - excess; i++)
        {
            fourBites += 84 * static_cast<uint32_t>(pow(85, i));
        }
        for(int i = 3; i >= 5 - excess; i--)
        {
            bite = 0;
            bite = fourBites / static_cast<uint32_t>(pow(2, i * 8));
            fourBites -= bite * static_cast<uint32_t>(pow(2, i * 8));
            if(bite < 33 || bite > 127)
                return 1;
            output << static_cast<char>(bite);
        }
    }
    return 0;
}
