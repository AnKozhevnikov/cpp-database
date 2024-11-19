#include <DataBase.h>

#include <stdexcept>

bool DataBase::StringCell::opG(const std::unique_ptr<Cell> &right) const
{
    return value > dynamic_cast<const StringCell &>(*right).value;
}

bool DataBase::StringCell::opL(const std::unique_ptr<Cell> &right) const
{
    return value < dynamic_cast<const StringCell &>(*right).value;
}

bool DataBase::StringCell::opEq(const std::unique_ptr<Cell> &right) const
{
    return value == dynamic_cast<const StringCell &>(*right).value;
}

bool DataBase::StringCell::opGeq(const std::unique_ptr<Cell> &right) const
{
    return value >= dynamic_cast<const StringCell &>(*right).value;
}

bool DataBase::StringCell::opLeq(const std::unique_ptr<Cell> &right) const
{
    return value <= dynamic_cast<const StringCell &>(*right).value;
}

bool DataBase::StringCell::opNeq(const std::unique_ptr<Cell> &right) const
{
    return value != dynamic_cast<const StringCell &>(*right).value;
}

std::unique_ptr<DataBase::Cell> DataBase::StringCell::opPlus(const std::unique_ptr<Cell> &right) const
{
    return std::make_unique<StringCell>(value + dynamic_cast<const StringCell &>(*right).value);
}

int DataBase::StringCell::opAbs() const
{
    return value.length();
}
