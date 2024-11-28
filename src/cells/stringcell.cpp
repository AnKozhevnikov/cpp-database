#include "Cell.h"

#include <stdexcept>

std::string StringCell::toString()
{
    return '"' + value + '"';
}

std::unique_ptr<Cell> StringCell::clone()
{
    return std::make_unique<StringCell>(value);
}

std::unique_ptr<Cell> StringCell::opG(const std::unique_ptr<Cell> &right) const
{
    return std::make_unique<BoolCell>(value.compare(dynamic_cast<const StringCell &>(*right).value) > 0);
}

std::unique_ptr<Cell> StringCell::opL(const std::unique_ptr<Cell> &right) const
{
    return std::make_unique<BoolCell>(value.compare(dynamic_cast<const StringCell &>(*right).value) < 0);
}

std::unique_ptr<Cell> StringCell::opEq(const std::unique_ptr<Cell> &right) const
{
    return std::make_unique<BoolCell>(value.compare(dynamic_cast<const StringCell &>(*right).value) == 0);
}

std::unique_ptr<Cell> StringCell::opGeq(const std::unique_ptr<Cell> &right) const
{
    return std::make_unique<BoolCell>(opG(right) || opEq(right));
}

std::unique_ptr<Cell> StringCell::opLeq(const std::unique_ptr<Cell> &right) const
{
    return std::make_unique<BoolCell>(opL(right) || opEq(right));
}

std::unique_ptr<Cell> StringCell::opNeq(const std::unique_ptr<Cell> &right) const
{
    return std::make_unique<BoolCell>(!opEq(right));
}

std::unique_ptr<Cell> StringCell::opPlus(const std::unique_ptr<Cell> &right) const
{
    return std::make_unique<StringCell>(value + dynamic_cast<const StringCell &>(*right).value);
}

std::unique_ptr<Cell> StringCell::opAbs() const
{
    return std::make_unique<IntCell>(value.length());
}

std::any StringCell::getValue() const
{
    return value;
}