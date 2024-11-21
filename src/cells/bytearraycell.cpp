#include <DataBase.h>

#include <stdexcept>

// A few assumption should I make before coding
// 1. vector.size() == sz
// 2. Different sz == different byte arrays and no leading zeros
// 3. BigEndian

DataBase::ByteArrayCell::ByteArrayCell(std::string s)
{
    for (size_t i = 0; i != s.size(); i++)
    {
        value.push_back(s[i]-'0');
    }
}

std::string DataBase::ByteArrayCell::toString()
{
    std::string ret;
    for (int8_t byte : value)
    {
        ret += std::to_string(byte);
    }
    return ret;
}

std::unique_ptr<DataBase::Cell> DataBase::ByteArrayCell::clone()
{
    return std::make_unique<ByteArrayCell>(value);
}

bool DataBase::ByteArrayCell::opEq(const std::unique_ptr<Cell> &right) const
{
    const std::vector<int8_t> &right_value = dynamic_cast<const ByteArrayCell &>(*right).value;
    for (size_t i = 0; i != right_value.size(); i++)
    {
        if (value[i] != right_value[i])
            return false;
    }
    return true;
}

bool DataBase::ByteArrayCell::opG(const std::unique_ptr<Cell> &right) const
{
    const std::vector<int8_t> &right_value = dynamic_cast<const ByteArrayCell &>(*right).value;
    for (size_t i = 0; i != right_value.size(); i++)
    {
        if (value[i] != right_value[i])
            return value[i] > right_value[i];
    }
    return false;
}

bool DataBase::ByteArrayCell::opL(const std::unique_ptr<Cell> &right) const
{
    return !opG(right) && !opEq(right);
}

bool DataBase::ByteArrayCell::opGeq(const std::unique_ptr<Cell> &right) const
{
    return opG(right) || opEq(right);
}

bool DataBase::ByteArrayCell::opLeq(const std::unique_ptr<Cell> &right) const
{
    return !opG(right);
}

bool DataBase::ByteArrayCell::opNeq(const std::unique_ptr<Cell> &right) const
{
    return !opEq(right);
}
