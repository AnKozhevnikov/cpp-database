#include <DataBase.h>

#include <stdexcept>   

std::unique_ptr<DataBase::Cell> DataBase::Cell::opPlus(const std::unique_ptr<Cell> &right) const
{
    throw std::runtime_error("This operation is not implemented");
}

std::unique_ptr<DataBase::Cell> DataBase::Cell::opMinus(const std::unique_ptr<Cell> &right) const
{
    throw std::runtime_error("This operation is not implemented");
}

std::unique_ptr<DataBase::Cell> DataBase::Cell::opMult(const std::unique_ptr<Cell> &right) const
{
    throw std::runtime_error("This operation is not implemented");
}

std::unique_ptr<DataBase::Cell> DataBase::Cell::opDiv(const std::unique_ptr<Cell> &right) const
{
    throw std::runtime_error("This operation is not implemented");
}

std::unique_ptr<DataBase::Cell> DataBase::Cell::opMod(const std::unique_ptr<Cell> &right) const
{
    throw std::runtime_error("This operation is not implemented");
}

bool DataBase::Cell::opG(const std::unique_ptr<Cell> &right) const
{
    throw std::runtime_error("This operation is not implemented");
}

bool DataBase::Cell::opL(const std::unique_ptr<Cell> &right) const
{
    throw std::runtime_error("This operation is not implemented");
}

bool DataBase::Cell::opEq(const std::unique_ptr<Cell> &right) const
{
    throw std::runtime_error("This operation is not implemented");
}

bool DataBase::Cell::opGeq(const std::unique_ptr<Cell> &right) const
{
    throw std::runtime_error("This operation is not implemented");
}

bool DataBase::Cell::opLeq(const std::unique_ptr<Cell> &right) const
{
    throw std::runtime_error("This operation is not implemented");
}

bool DataBase::Cell::opNeq(const std::unique_ptr<Cell> &right) const
{
    throw std::runtime_error("This operation is not implemented");
}

std::unique_ptr<DataBase::Cell> DataBase::Cell::opAnd(const std::unique_ptr<Cell> &right) const
{
    throw std::runtime_error("This operation is not implemented");
}

std::unique_ptr<DataBase::Cell> DataBase::Cell::opOr(const std::unique_ptr<Cell> &right) const
{
    throw std::runtime_error("This operation is not implemented");
}

std::unique_ptr<DataBase::Cell> DataBase::Cell::opNot() const
{
    throw std::runtime_error("This operation is not implemented");
}

std::unique_ptr<DataBase::Cell> DataBase::Cell::opXor(const std::unique_ptr<Cell> &right) const
{
    throw std::runtime_error("This operation is not implemented");
}

int DataBase::Cell::opAbs() const
{
    throw std::runtime_error("This operation is not implemented");
}