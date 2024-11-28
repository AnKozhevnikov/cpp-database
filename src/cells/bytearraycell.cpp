#include "Cell.h"

#include <stdexcept>

// A few assumption should I make before coding
// 1. vector.size() == sz
// 2. Different sz == different byte arrays and no leading zeros
// 3. BigEndian

std::string ByteArrayCell::toString()
{
    std::string ret;
    for (int8_t byte : value)
    {
        ret += std::to_string(byte);
    }
    return ret;
}

std::unique_ptr<Cell> ByteArrayCell::clone()
{
    return std::make_unique<ByteArrayCell>(value);
}

std::unique_ptr<Cell> ByteArrayCell::opEq(const std::unique_ptr<Cell> &right) const
{
    const std::vector<int8_t> &right_value = dynamic_cast<const ByteArrayCell &>(*right).value;
    for (size_t i = 0; i != right_value.size(); i++)
    {
        if (value[i] != right_value[i])
            return std::make_unique<BoolCell>(false);
    }
    return std::make_unique<BoolCell>(true);
}

std::unique_ptr<Cell> ByteArrayCell::opG(const std::unique_ptr<Cell> &right) const
{
    const std::vector<int8_t> &right_value = dynamic_cast<const ByteArrayCell &>(*right).value;
    for (size_t i = 0; i != right_value.size(); i++)
    {
        if (value[i] != right_value[i])
            return std::make_unique<BoolCell>(value[i] > right_value[i]);
    }
    return std::make_unique<BoolCell>(false);
}

std::unique_ptr<Cell> ByteArrayCell::opL(const std::unique_ptr<Cell> &right) const
{
    const std::vector<int8_t> &right_value = dynamic_cast<const ByteArrayCell &>(*right).value;
    for (size_t i = 0; i != right_value.size(); i++)
    {
        if (value[i] != right_value[i])
            return std::make_unique<BoolCell>(value[i] < right_value[i]);
    }
    return std::make_unique<BoolCell>(false);
}

std::unique_ptr<Cell> ByteArrayCell::opGeq(const std::unique_ptr<Cell> &right) const
{
    const std::vector<int8_t> &right_value = dynamic_cast<const ByteArrayCell &>(*right).value;
    for (size_t i = 0; i != right_value.size(); i++)
    {
        if (value[i] != right_value[i])
            return std::make_unique<BoolCell>(value[i] >= right_value[i]);
    }
    return std::make_unique<BoolCell>(true);
}

std::unique_ptr<Cell> ByteArrayCell::opLeq(const std::unique_ptr<Cell> &right) const
{
    const std::vector<int8_t> &right_value = dynamic_cast<const ByteArrayCell &>(*right).value;
    for (size_t i = 0; i != right_value.size(); i++)
    {
        if (value[i] != right_value[i])
            return std::make_unique<BoolCell>(value[i] <= right_value[i]);
    }
    return std::make_unique<BoolCell>(true);
}

std::unique_ptr<Cell> ByteArrayCell::opNeq(const std::unique_ptr<Cell> &right) const
{
    const std::vector<int8_t> &right_value = dynamic_cast<const ByteArrayCell &>(*right).value;
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