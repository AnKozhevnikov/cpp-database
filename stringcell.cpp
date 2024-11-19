#include <DataBase.h>

#include <stdexcept>

bool DataBase::StringCell::opG(const std::unique_ptr<Cell> &right) const
{
    return value.compare(dynamic_cast<const StringCell &>(*right).value) > 0;
}

bool DataBase::StringCell::opL(const std::unique_ptr<Cell> &right) const
{
    return value.compare(dynamic_cast<const StringCell &>(*right).value) < 0;
}

bool DataBase::StringCell::opEq(const std::unique_ptr<Cell> &right) const
{
    return value.compare(dynamic_cast<const StringCell &>(*right).value) == 0;
}

bool DataBase::StringCell::opGeq(const std::unique_ptr<Cell> &right) const
{
    return opG(right) || opEq(right);
}

bool DataBase::StringCell::opLeq(const std::unique_ptr<Cell> &right) const
{
    return opL(right) || opEq(right);
}

bool DataBase::StringCell::opNeq(const std::unique_ptr<Cell> &right) const
{
    return !opEq(right);
}

std::unique_ptr<DataBase::Cell> DataBase::StringCell::opPlus(const std::unique_ptr<Cell> &right) const
{
    return std::make_unique<StringCell>(value + dynamic_cast<const StringCell &>(*right).value);
}

int DataBase::StringCell::opAbs() const
{
    return value.length();
}
