#include "Cell.h"

#include <stdexcept>

// A few assumption should I make before coding
// 1. vector.size() == sz
// 2. Different sz == different byte arrays and no leading zeros
// 3. BigEndian

std::string ByteArrayCell::toString()
{
    std::string ret = "0x";
    for (int i = 0; i < value.size(); i++)
    {
        int c1 = value[i] / 16;
        int c2 = value[i] % 16;
        ret += (c1 < 10 ? '0' + c1 : 'a' + c1 - 10);
        ret += (c2 < 10 ? '0' + c2 : 'a' + c2 - 10);
    }
    return ret;
}

std::unique_ptr<Cell> ByteArrayCell::clone()
{
    return std::make_unique<ByteArrayCell>(value);
}

std::unique_ptr<Cell> ByteArrayCell::opEq(const std::unique_ptr<Cell> &right) const
{
    const std::vector<uint8_t> &right_value = dynamic_cast<const ByteArrayCell &>(*right).value;
    for (size_t i = 0; i != right_value.size(); i++)
    {
        if (value[i] != right_value[i])
            return std::make_unique<BoolCell>(false);
    }
    return std::make_unique<BoolCell>(true);
}

std::unique_ptr<Cell> ByteArrayCell::opG(const std::unique_ptr<Cell> &right) const
{
    const std::vector<uint8_t> &right_value = dynamic_cast<const ByteArrayCell &>(*right).value;
    for (size_t i = 0; i != right_value.size(); i++)
    {
        if (value[i] != right_value[i])
            return std::make_unique<BoolCell>(value[i] > right_value[i]);
    }
    return std::make_unique<BoolCell>(false);
}

std::unique_ptr<Cell> ByteArrayCell::opL(const std::unique_ptr<Cell> &right) const
{
    const std::vector<uint8_t> &right_value = dynamic_cast<const ByteArrayCell &>(*right).value;
    for (size_t i = 0; i != right_value.size(); i++)
    {
        if (value[i] != right_value[i])
            return std::make_unique<BoolCell>(value[i] < right_value[i]);
    }
    return std::make_unique<BoolCell>(false);
}

std::unique_ptr<Cell> ByteArrayCell::opGeq(const std::unique_ptr<Cell> &right) const
{
    const std::vector<uint8_t> &right_value = dynamic_cast<const ByteArrayCell &>(*right).value;
    for (size_t i = 0; i != right_value.size(); i++)
    {
        if (value[i] != right_value[i])
            return std::make_unique<BoolCell>(value[i] >= right_value[i]);
    }
    return std::make_unique<BoolCell>(true);
}

std::unique_ptr<Cell> ByteArrayCell::opLeq(const std::unique_ptr<Cell> &right) const
{
    const std::vector<uint8_t> &right_value = dynamic_cast<const ByteArrayCell &>(*right).value;
    for (size_t i = 0; i != right_value.size(); i++)
    {
        if (value[i] != right_value[i])
            return std::make_unique<BoolCell>(value[i] <= right_value[i]);
    }
    return std::make_unique<BoolCell>(true);
}

std::unique_ptr<Cell> ByteArrayCell::opNeq(const std::unique_ptr<Cell> &right) const
{
    const std::vector<uint8_t> &right_value = dynamic_cast<const ByteArrayCell &>(*right).value;
    for (size_t i = 0; i != right_value.size(); i++)
    {
        if (value[i] != right_value[i])
            return std::make_unique<BoolCell>(true);
    }
    return std::make_unique<BoolCell>(false);
}

std::unique_ptr<Cell> ByteArrayCell::opAbs() const
{
    return std::make_unique<IntCell>(value.size());
}

std::any ByteArrayCell::getValue() const
{
    return value;
}