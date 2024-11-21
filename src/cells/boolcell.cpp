#include <DataBase.h>

#include <stdexcept>

std::string DataBase::BoolCell::toString()
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

std::unique_ptr<DataBase::Cell> DataBase::BoolCell::clone()
{
    return std::make_unique<BoolCell>(value);
}

bool DataBase::BoolCell::opG(const std::unique_ptr<Cell> &right) const
{
    return value > dynamic_cast<const BoolCell &>(*right).value;
}

bool DataBase::BoolCell::opL(const std::unique_ptr<Cell> &right) const
{
    return value < dynamic_cast<const BoolCell &>(*right).value;
}

bool DataBase::BoolCell::opEq(const std::unique_ptr<Cell> &right) const
{
    return value == dynamic_cast<const BoolCell &>(*right).value;
}

bool DataBase::BoolCell::opGeq(const std::unique_ptr<Cell> &right) const
{
    return value >= dynamic_cast<const BoolCell &>(*right).value;
}

bool DataBase::BoolCell::opLeq(const std::unique_ptr<Cell> &right) const
{
    return value <= dynamic_cast<const BoolCell &>(*right).value;
}

bool DataBase::BoolCell::opNeq(const std::unique_ptr<Cell> &right) const
{
    return value != dynamic_cast<const BoolCell &>(*right).value;
}

std::unique_ptr<DataBase::Cell> DataBase::BoolCell::opOr(const std::unique_ptr<Cell> &right) const
{
    return std::make_unique<BoolCell>(value || dynamic_cast<const BoolCell &>(*right).value);
}

std::unique_ptr<DataBase::Cell> DataBase::BoolCell::opAnd(const std::unique_ptr<Cell> &right) const
{
    return std::make_unique<BoolCell>(value && dynamic_cast<const BoolCell &>(*right).value);
}

std::unique_ptr<DataBase::Cell> DataBase::BoolCell::opNot() const
{
    return std::make_unique<BoolCell>(!value);
}
