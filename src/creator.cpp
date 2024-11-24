#include <stdexcept>

#include "Creator.h"
#include "Cell.h"
#include "DataBase.h"

std::unique_ptr<Cell> Creator::generateCell(std::shared_ptr<ValueType> vtype, std::any arg)
{
    switch (vtype->type)
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

std::optional<std::any> Creator::generateValue(std::shared_ptr<ValueType> vtype, std::string s)
{
    switch (vtype->type)
    {
    case Int:
        return std::stoi(s);
    case Bool:
        return s == "1";
    case String:
        return s;
    case ByteArray: {
        std::vector<int8_t> v;
        for (int i = 0; i < s.size(); ++i)
        {
            v.push_back(s[i] - '0');
        }
        return v;
    }
    default:
        throw std::invalid_argument("Invalid type");
    }
}

std::shared_ptr<ValueType> Creator::generateValueType(std::string s)
{
    std::string args;
    if (s.back() == ']')
    {
        int i = s.size() - 2;
        while (s[i] != '[')
        {
            args = s[i] + args;
            i--;
        }
        s = s.substr(0, i);
    }

    if (s == std::to_string(Int))
    {
        return std::make_shared<ValueType>(Int);
    }
    else if (s == std::to_string(Bool))
    {
        return std::make_shared<ValueType>(Bool);
    }
    else if (s == std::to_string(String))
    {
        return std::make_shared<ValueType>(String);
    }
    else if (s == std::to_string(ByteArray))
    {
        return std::make_shared<ByteArrayType>(std::stoi(args));
    }
    else
    {
        throw std::invalid_argument("Invalid type");
    }
}