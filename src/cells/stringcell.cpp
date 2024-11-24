#include "Cell.h"

#include <stdexcept>

std::string StringCell::toString()
{
    return value;
}

std::unique_ptr<Cell> StringCell::clone()
{
    return std::make_unique<StringCell>(value);
}

bool StringCell::opG(const std::unique_ptr<Cell> &right) const
{
    return value.compare(dynamic_cast<const StringCell &>(*right).value) > 0;
}

bool StringCell::opL(const std::unique_ptr<Cell> &right) const
{
    return value.compare(dynamic_cast<const StringCell &>(*right).value) < 0;
}

bool StringCell::opEq(const std::unique_ptr<Cell> &right) const
{
    return value.compare(dynamic_cast<const StringCell &>(*right).value) == 0;
}

bool StringCell::opGeq(const std::unique_ptr<Cell> &right) const
{
    return opG(right) || opEq(right);
}

bool StringCell::opLeq(const std::unique_ptr<Cell> &right) const
{
    return opL(right) || opEq(right);
}

bool StringCell::opNeq(const std::unique_ptr<Cell> &right) const
{
    return !opEq(right);
}

std::unique_ptr<Cell> StringCell::opPlus(const std::unique_ptr<Cell> &right) const
{
    return std::make_unique<StringCell>(value + dynamic_cast<const StringCell &>(*right).value);
}

int StringCell::opAbs() const
{
    return value.length();
}
