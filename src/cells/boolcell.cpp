#include "Cell.h"

#include <stdexcept>

std::string BoolCell::toString()
{
    std::string ret;
    if (value)
    {
        ret = "1";
    }
    else
    {
        ret = "0";
    }
    return ret;
}

std::unique_ptr<Cell> BoolCell::clone()
{
    return std::make_unique<BoolCell>(value);
}

bool BoolCell::opG(const std::unique_ptr<Cell> &right) const
{
    return value > dynamic_cast<const BoolCell &>(*right).value;
}

bool BoolCell::opL(const std::unique_ptr<Cell> &right) const
{
    return value < dynamic_cast<const BoolCell &>(*right).value;
}

bool BoolCell::opEq(const std::unique_ptr<Cell> &right) const
{
    return value == dynamic_cast<const BoolCell &>(*right).value;
}

bool BoolCell::opGeq(const std::unique_ptr<Cell> &right) const
{
    return value >= dynamic_cast<const BoolCell &>(*right).value;
}

bool BoolCell::opLeq(const std::unique_ptr<Cell> &right) const
{
    return value <= dynamic_cast<const BoolCell &>(*right).value;
}

bool BoolCell::opNeq(const std::unique_ptr<Cell> &right) const
{
    return value != dynamic_cast<const BoolCell &>(*right).value;
}

std::unique_ptr<Cell> BoolCell::opOr(const std::unique_ptr<Cell> &right) const
{
    return std::make_unique<BoolCell>(value || dynamic_cast<const BoolCell &>(*right).value);
}

std::unique_ptr<Cell> BoolCell::opAnd(const std::unique_ptr<Cell> &right) const
{
    return std::make_unique<BoolCell>(value && dynamic_cast<const BoolCell &>(*right).value);
}

std::unique_ptr<Cell> BoolCell::opNot() const
{
    return std::make_unique<BoolCell>(!value);
}
