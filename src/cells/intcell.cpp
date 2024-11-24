#include "Cell.h"
#include <stdexcept>

std::string IntCell::toString() {
    return std::to_string(value);
}

void IntCell::inc() {
    ++value;
}

std::unique_ptr<Cell> IntCell::clone() {
    return std::make_unique<IntCell>(value);
}

std::unique_ptr<Cell> IntCell::opPlus(const std::unique_ptr<Cell> &right) const
{
    return std::make_unique<IntCell>(value + dynamic_cast<const IntCell &>(*right).value);
}

std::unique_ptr<Cell> IntCell::opMinus(const std::unique_ptr<Cell> &right) const
{
    return std::make_unique<IntCell>(value - dynamic_cast<const IntCell &>(*right).value);
}

std::unique_ptr<Cell> IntCell::opMult(const std::unique_ptr<Cell> &right) const
{
    return std::make_unique<IntCell>(value * dynamic_cast<const IntCell &>(*right).value);
}

std::unique_ptr<Cell> IntCell::opDiv(const std::unique_ptr<Cell> &right) const
{
    return std::make_unique<IntCell>(value / dynamic_cast<const IntCell &>(*right).value);
}

std::unique_ptr<Cell> IntCell::opMod(const std::unique_ptr<Cell> &right) const
{
    return std::make_unique<IntCell>(value % dynamic_cast<const IntCell &>(*right).value);
}

bool IntCell::opG(const std::unique_ptr<Cell> &right) const
{
    return value > dynamic_cast<const IntCell &>(*right).value;
}

bool IntCell::opL(const std::unique_ptr<Cell> &right) const
{
    return value < dynamic_cast<const IntCell &>(*right).value;
}

bool IntCell::opEq(const std::unique_ptr<Cell> &right) const
{
    return value == dynamic_cast<const IntCell &>(*right).value;
}

bool IntCell::opGeq(const std::unique_ptr<Cell> &right) const
{
    return value >= dynamic_cast<const IntCell &>(*right).value;
}

bool IntCell::opLeq(const std::unique_ptr<Cell> &right) const
{
    return value <= dynamic_cast<const IntCell &>(*right).value;
}

bool IntCell::opNeq(const std::unique_ptr<Cell> &right) const
{
    return value != dynamic_cast<const IntCell &>(*right).value;
}


