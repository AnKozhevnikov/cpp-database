#include "Cell.h"

#include <stdexcept>

std::string BoolCell::toString()
{
    std::string ret;
    if (value)
    {
        ret = "True";
    }
    else
    {
        ret = "False";
    }
    return ret;
}

std::unique_ptr<Cell> BoolCell::clone()
{
    return std::make_unique<BoolCell>(value);
}

std::unique_ptr<Cell> BoolCell::opG(const std::unique_ptr<Cell> &right) const
{
    return std::make_unique<BoolCell>(value > dynamic_cast<const BoolCell &>(*right).value);
}

std::unique_ptr<Cell> BoolCell::opL(const std::unique_ptr<Cell> &right) const
{
    return std::make_unique<BoolCell>(value < dynamic_cast<const BoolCell &>(*right).value);
}

std::unique_ptr<Cell> BoolCell::opEq(const std::unique_ptr<Cell> &right) const
{
    return std::make_unique<BoolCell>(value == dynamic_cast<const BoolCell &>(*right).value);
}

std::unique_ptr<Cell> BoolCell::opGeq(const std::unique_ptr<Cell> &right) const
{
    return std::make_unique<BoolCell>(value >= dynamic_cast<const BoolCell &>(*right).value);
}

std::unique_ptr<Cell> BoolCell::opLeq(const std::unique_ptr<Cell> &right) const
{
    return std::make_unique<BoolCell>(value <= dynamic_cast<const BoolCell &>(*right).value);
}

std::unique_ptr<Cell> BoolCell::opNeq(const std::unique_ptr<Cell> &right) const
{
    return std::make_unique<BoolCell>(value != dynamic_cast<const BoolCell &>(*right).value);
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

std::any BoolCell::getValue() const
{
    return value;
}
