#include "Cell.h"

#include <stdexcept>   

std::string Cell::toString() {
    throw std::runtime_error("This operation is not implemented");
}

void Cell::inc() {
    throw std::runtime_error("This operation is not implemented");
}

std::unique_ptr<Cell> Cell::opPlus(const std::unique_ptr<Cell> &right) const
{
    throw std::runtime_error("This operation is not implemented");
}

std::unique_ptr<Cell> Cell::opMinus(const std::unique_ptr<Cell> &right) const
{
    throw std::runtime_error("This operation is not implemented");
}

std::unique_ptr<Cell> Cell::opMult(const std::unique_ptr<Cell> &right) const
{
    throw std::runtime_error("This operation is not implemented");
}

std::unique_ptr<Cell> Cell::opDiv(const std::unique_ptr<Cell> &right) const
{
    throw std::runtime_error("This operation is not implemented");
}

std::unique_ptr<Cell> Cell::opMod(const std::unique_ptr<Cell> &right) const
{
    throw std::runtime_error("This operation is not implemented");
}

std::unique_ptr<Cell> Cell::opG(const std::unique_ptr<Cell> &right) const
{
    throw std::runtime_error("This operation is not implemented");
}

std::unique_ptr<Cell> Cell::opL(const std::unique_ptr<Cell> &right) const
{
    throw std::runtime_error("This operation is not implemented");
}

std::unique_ptr<Cell> Cell::opEq(const std::unique_ptr<Cell> &right) const
{
    throw std::runtime_error("This operation is not implemented");
}

std::unique_ptr<Cell> Cell::opGeq(const std::unique_ptr<Cell> &right) const
{
    throw std::runtime_error("This operation is not implemented");
}

std::unique_ptr<Cell> Cell::opLeq(const std::unique_ptr<Cell> &right) const
{
    throw std::runtime_error("This operation is not implemented");
}

std::unique_ptr<Cell> Cell::opNeq(const std::unique_ptr<Cell> &right) const
{
    throw std::runtime_error("This operation is not implemented");
}

std::unique_ptr<Cell> Cell::opAnd(const std::unique_ptr<Cell> &right) const
{
    throw std::runtime_error("This operation is not implemented");
}

std::unique_ptr<Cell> Cell::opOr(const std::unique_ptr<Cell> &right) const
{
    throw std::runtime_error("This operation is not implemented");
}

std::unique_ptr<Cell> Cell::opNot() const
{
    throw std::runtime_error("This operation is not implemented");
}

std::unique_ptr<Cell> Cell::opXor(const std::unique_ptr<Cell> &right) const
{
    throw std::runtime_error("This operation is not implemented");
}

std::unique_ptr<Cell> Cell::opAbs() const
{
    throw std::runtime_error("This operation is not implemented");
}