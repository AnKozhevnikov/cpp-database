#include "DataBase.h"
#include <gtest/gtest.h>

TEST(ReadRawNoType, Int)
{
    std::unique_ptr<Cell> c1 = Creator::cellFromRawString("5");
    EXPECT_EQ(std::any_cast<int>(c1->getValue()), 5);

    std::unique_ptr<Cell> c2 = Creator::cellFromRawString("0");
    EXPECT_EQ(std::any_cast<int>(c2->getValue()), 0);

    std::unique_ptr<Cell> c3 = Creator::cellFromRawString("-5");
    EXPECT_EQ(std::any_cast<int>(c3->getValue()), -5);

    std::unique_ptr<Cell> c4 = Creator::cellFromRawString("1000000000");
    EXPECT_EQ(std::any_cast<int>(c4->getValue()), 1000000000);

    std::unique_ptr<Cell> c5 = Creator::cellFromRawString("-1000000000");
    EXPECT_EQ(std::any_cast<int>(c5->getValue()), -1000000000);

    std::unique_ptr<Cell> c6 = Creator::cellFromRawString("2147483647");
    EXPECT_EQ(std::any_cast<int>(c6->getValue()), 2147483647);

    std::unique_ptr<Cell> c7 = Creator::cellFromRawString("-2147483648");
    EXPECT_EQ(std::any_cast<int>(c7->getValue()), -2147483648);
}

TEST(ReadRawNoType, Bool)
{
    std::unique_ptr<Cell> c1 = Creator::cellFromRawString("True");
    EXPECT_EQ(std::any_cast<bool>(c1->getValue()), true);

    std::unique_ptr<Cell> c2 = Creator::cellFromRawString("False");
    EXPECT_EQ(std::any_cast<bool>(c2->getValue()), false);

    std::unique_ptr<Cell> c3 = Creator::cellFromRawString("true");
    EXPECT_EQ(std::any_cast<bool>(c3->getValue()), true);

    std::unique_ptr<Cell> c4 = Creator::cellFromRawString("false");
    EXPECT_EQ(std::any_cast<bool>(c4->getValue()), false);
}

TEST(ReadRawNoType, String)
{
    std::unique_ptr<Cell> c1 = Creator::cellFromRawString("\"Hello\"");
    EXPECT_EQ(std::any_cast<std::string>(c1->getValue()), "Hello");

    std::unique_ptr<Cell> c2 = Creator::cellFromRawString("\"\"");
    EXPECT_EQ(std::any_cast<std::string>(c2->getValue()), "");
}

TEST(ReadRawNoType, ByteArray)
{
    std::unique_ptr<Cell> c1 = Creator::cellFromRawString("0x00");
    std::vector<uint8_t> v1 = {0};
    EXPECT_EQ(std::any_cast<std::vector<uint8_t>>(c1->getValue()), v1);

    std::unique_ptr<Cell> c2 = Creator::cellFromRawString("0x01");
    std::vector<uint8_t> v2 = {1};
    EXPECT_EQ(std::any_cast<std::vector<uint8_t>>(c2->getValue()), v2);

    std::unique_ptr<Cell> c3 = Creator::cellFromRawString("0x10");
    std::vector<uint8_t> v3 = {16};
    EXPECT_EQ(std::any_cast<std::vector<uint8_t>>(c3->getValue()), v3);

    std::unique_ptr<Cell> c4 = Creator::cellFromRawString("0x0f");
    std::vector<uint8_t> v4 = {15};
    EXPECT_EQ(std::any_cast<std::vector<uint8_t>>(c4->getValue()), v4);

    std::unique_ptr<Cell> c5 = Creator::cellFromRawString("0x0a0b0c0d");
    std::vector<uint8_t> v5 = {10, 11, 12, 13};
    EXPECT_EQ(std::any_cast<std::vector<uint8_t>>(c5->getValue()), v5);

    std::unique_ptr<Cell> c6 = Creator::cellFromRawString("0x0a0b0c0d0e0f");
    std::vector<uint8_t> v6 = {10, 11, 12, 13, 14, 15};
    EXPECT_EQ(std::any_cast<std::vector<uint8_t>>(c6->getValue()), v6);
}

TEST(ReadRawWithType, Int)
{
    std::unique_ptr<Cell> c1 = Creator::cellFromRawString("(Int)5");
    EXPECT_EQ(std::any_cast<int>(c1->getValue()), 5);

    std::unique_ptr<Cell> c2 = Creator::cellFromRawString("(int)0");
    EXPECT_EQ(std::any_cast<int>(c2->getValue()), 0);

    std::unique_ptr<Cell> c3 = Creator::cellFromRawString("(Int)-5");
    EXPECT_EQ(std::any_cast<int>(c3->getValue()), -5);

    std::unique_ptr<Cell> c4 = Creator::cellFromRawString("(int)1000000000");
    EXPECT_EQ(std::any_cast<int>(c4->getValue()), 1000000000);

    std::unique_ptr<Cell> c5 = Creator::cellFromRawString("(Int)-1000000000");
    EXPECT_EQ(std::any_cast<int>(c5->getValue()), -1000000000);

    std::unique_ptr<Cell> c6 = Creator::cellFromRawString("(int)2147483647");
    EXPECT_EQ(std::any_cast<int>(c6->getValue()), 2147483647);

    std::unique_ptr<Cell> c7 = Creator::cellFromRawString("(Int)-2147483648");
    EXPECT_EQ(std::any_cast<int>(c7->getValue()), -2147483648);
}

TEST(ReadRawWithType, Bool)
{
    std::unique_ptr<Cell> c1 = Creator::cellFromRawString("(Bool)True");
    EXPECT_EQ(std::any_cast<bool>(c1->getValue()), true);

    std::unique_ptr<Cell> c2 = Creator::cellFromRawString("(bool)False");
    EXPECT_EQ(std::any_cast<bool>(c2->getValue()), false);

    std::unique_ptr<Cell> c3 = Creator::cellFromRawString("(Bool)true");
    EXPECT_EQ(std::any_cast<bool>(c3->getValue()), true);

    std::unique_ptr<Cell> c4 = Creator::cellFromRawString("(bool)false");
    EXPECT_EQ(std::any_cast<bool>(c4->getValue()), false);
}

TEST(ReadRawWithType, String)
{
    std::unique_ptr<Cell> c1 = Creator::cellFromRawString("(String)\"Hello\"");
    EXPECT_EQ(std::any_cast<std::string>(c1->getValue()), "Hello");

    std::unique_ptr<Cell> c2 = Creator::cellFromRawString("(string)\"\"");
    EXPECT_EQ(std::any_cast<std::string>(c2->getValue()), "");
}

TEST(ReadRawWithType, ByteArray0x)
{
    std::unique_ptr<Cell> c1 = Creator::cellFromRawString("(ByteArray[1])0x00");
    std::vector<uint8_t> v1 = {0};
    EXPECT_EQ(std::any_cast<std::vector<uint8_t>>(c1->getValue()), v1);

    std::unique_ptr<Cell> c2 = Creator::cellFromRawString("(bytearray[1])0x01");
    std::vector<uint8_t> v2 = {1};
    EXPECT_EQ(std::any_cast<std::vector<uint8_t>>(c2->getValue()), v2);

    std::unique_ptr<Cell> c3 = Creator::cellFromRawString("(ByteArray[1])0x10");
    std::vector<uint8_t> v3 = {16};
    EXPECT_EQ(std::any_cast<std::vector<uint8_t>>(c3->getValue()), v3);

    std::unique_ptr<Cell> c4 = Creator::cellFromRawString("(bytearray[1])0x0f");
    std::vector<uint8_t> v4 = {15};
    EXPECT_EQ(std::any_cast<std::vector<uint8_t>>(c4->getValue()), v4);

    std::unique_ptr<Cell> c5 = Creator::cellFromRawString("(ByteArray[4])0x0a0b0c0d");
    std::vector<uint8_t> v5 = {10, 11, 12, 13};
    EXPECT_EQ(std::any_cast<std::vector<uint8_t>>(c5->getValue()), v5);

    std::unique_ptr<Cell> c6 = Creator::cellFromRawString("(bytearray[6])0x0a0b0c0d0e0f");
    std::vector<uint8_t> v6 = {10, 11, 12, 13, 14, 15};
    EXPECT_EQ(std::any_cast<std::vector<uint8_t>>(c6->getValue()), v6);
}
