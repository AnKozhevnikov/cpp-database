#include "DataBase.h"

std::unique_ptr<DataBase::Cell> DataBase::Creator::generateCell(Types type, std::any arg)
{
    switch (type)
    {
    case Int:
        return std::make_unique<IntCell>(std::any_cast<int>(arg));
    case Bool:
        return std::make_unique<BoolCell>(std::any_cast<bool>(arg));
    case String:
        return std::make_unique<StringCell>(std::any_cast<std::string>(arg));
    case ByteArray:
        return std::make_unique<ByteArrayCell>(std::any_cast<std::vector<int8_t>>(arg));
    default:
        throw std::invalid_argument("Invalid type");
    }
}