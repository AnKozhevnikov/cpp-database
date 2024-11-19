#include <DataBase.h>
#include <stdexcept>

std::unique_ptr<DataBase::Cell> DataBase::IntCell::opPlus(const std::unique_ptr<Cell> &right) const
{
    return std::make_unique<IntCell>(value + dynamic_cast<const IntCell &>(*right).value);
}

std::unique_ptr<DataBase::Cell> DataBase::IntCell::opMinus(const std::unique_ptr<Cell> &right) const
{
    return std::make_unique<IntCell>(value - dynamic_cast<const IntCell &>(*right).value);
}

std::unique_ptr<DataBase::Cell> DataBase::IntCell::opMult(const std::unique_ptr<Cell> &right) const
{
    return std::make_unique<IntCell>(value * dynamic_cast<const IntCell &>(*right).value);
}

std::unique_ptr<DataBase::Cell> DataBase::IntCell::opDiv(const std::unique_ptr<Cell> &right) const
{
    return std::make_unique<IntCell>(value / dynamic_cast<const IntCell &>(*right).value);
}

std::unique_ptr<DataBase::Cell> DataBase::IntCell::opMod(const std::unique_ptr<Cell> &right) const
{
    return std::make_unique<IntCell>(value % dynamic_cast<const IntCell &>(*right).value);
}

bool DataBase::IntCell::opG(const std::unique_ptr<Cell> &right) const
{
    return value > dynamic_cast<const IntCell &>(*right).value;
}

bool DataBase::IntCell::opL(const std::unique_ptr<Cell> &right) const
{
    return value < dynamic_cast<const IntCell &>(*right).value;
}

bool DataBase::IntCell::opEq(const std::unique_ptr<Cell> &right) const
{
    return value == dynamic_cast<const IntCell &>(*right).value;
}

bool DataBase::IntCell::opGeq(const std::unique_ptr<Cell> &right) const
{
    return value >= dynamic_cast<const IntCell &>(*right).value;
}

bool DataBase::IntCell::opLeq(const std::unique_ptr<Cell> &right) const
{
    return value <= dynamic_cast<const IntCell &>(*right).value;
}

bool DataBase::IntCell::opNeq(const std::unique_ptr<Cell> &right) const
{
    return value != dynamic_cast<const IntCell &>(*right).value;
}


