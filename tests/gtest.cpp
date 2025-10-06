#include "../coder.h"
#include <gtest/gtest.h>
#include <sstream>
#include <string>

TEST(CoderTest, Encode)
{
    std::string input = "Hello,ASCII85!";
    std::ostringstream encoded;

    encode(input, encoded);

    std::string encodedStr = encoded.str();
 
    EXPECT_EQ(encodedStr, "87cURD_+1Q6V0j/2'D"); 
}

TEST(CoderTest, EncodeDecodeCycle)
{
    std::string input = "Goodbye,ASCII85!";
    std::ostringstream encoded;
    std::ostringstream decoded;

    encode(input, encoded);

    std::string encodedStr = encoded.str();
    std::istringstream encodedStream(encodedStr);
    std::ostringstream decodedStream;

    int result = decode(encodedStr, decodedStream);

    EXPECT_EQ(result, 0); 
    EXPECT_EQ(decodedStream.str().substr(0, input.size()), input); 
}

TEST(CoderTest, DifferentInputSizes)
{
    std::vector<std::string> inputs = {
        "hgf", "fhdss", "kmksfaskn93", "oowuewssfvv.f", "ssppspspspsps", "/dosn.,9slssf''"
    };

    for (const auto& input : inputs) {
        std::ostringstream encoded;
        std::ostringstream decoded;

        encode(const_cast<std::string&>(input), encoded);

        std::string encodedStr = encoded.str();
        std::ostringstream output;
        int result = decode(encodedStr, output);

        EXPECT_EQ(result, 0);
        EXPECT_EQ(output.str().substr(0, input.size()), input);
    }
}

TEST(CoderTest, DecodeError)
{
    std::string badInput = "!!!!!";
    std::ostringstream output;
    int result = decode(badInput, output);
    EXPECT_EQ(result, 1);
}


TEST(CoderTest, EmptyString)
{
    std::string input = "";
    std::ostringstream encoded;
    encode(input, encoded);
    EXPECT_TRUE(encoded.str().empty());
}