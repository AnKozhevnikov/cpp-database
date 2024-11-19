#include <DataBase.h>

#include <stdexcept>

// A few assumption should I make before coding
// 1. vector.size() == sz
// 2. Different sz == different byte arrays and no leading zeros
// 3. BigEndian
bool DataBase::ByteArrayCell::opEq(const std::unique_ptr<Cell> &right) const
{
    if (dynamic_cast<const ByteArrayCell &>(*right).sz != sz)
        return false;
    const std::vector<int8_t> &right_value = dynamic_cast<const ByteArrayCell &>(*right).value;
    for (size_t i = 0; i != sz; i++)
    {
        if (value[i] != right_value[i])
            return false;
    }
    return true;
}
bool DataBase::ByteArrayCell::opG(const std::unique_ptr<Cell> &right) const
{
    if (dynamic_cast<const ByteArrayCell &>(*right).sz != sz)
        return sz > dynamic_cast<const ByteArrayCell &>(*right).sz;
    const std::vector<int8_t> &right_value = dynamic_cast<const ByteArrayCell &>(*right).value;
    for (size_t i = 0; i != sz; i++)
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
