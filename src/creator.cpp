#include <stdexcept>

#include "Cell.h"
#include "Creator.h"
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
        return std::make_unique<ByteArrayCell>(std::any_cast<std::vector<uint8_t>>(arg));
    default:
        throw std::invalid_argument("Invalid type");
    }
}

std::any Creator::generateValue(std::shared_ptr<ValueType> vtype, std::string s)
{
    switch (vtype->type)
    {
    case Int:
        return std::stoi(s);
    case Bool:
        return s == "true" || s == "True";
    case String:
        if (s[0] == '\"' && s.back() == '\"')
        {
            return s.substr(1, s.size() - 2);
        }
        else
        {
            throw std::invalid_argument("Invalid string");
        }
        return s;
    case ByteArray: {
        std::vector<uint8_t> v;
        if (s.size() >= 2 && s[0] == '0' && s[1] == 'x')
        {
            s = s.substr(2);
            if (s.size() % 2 != 0)
            {
                throw std::invalid_argument("Invalid bytearray size");
            }
            for (int i = 0; i < s.size(); i += 2)
            {
                if (!((s[i] >= '0' && s[i] <= '9') || (s[i] >= 'a' && s[i] <= 'f')))
                {
                    throw std::invalid_argument("Invalid bytearray value");
                }
                int c1 = s[i] >= '0' && s[i] <= '9' ? s[i] - '0' : s[i] - 'a' + 10;
                int c2 = s[i + 1] >= '0' && s[i + 1] <= '9' ? s[i + 1] - '0' : s[i + 1] - 'a' + 10;
                v.push_back(c1 * 16 + c2);
            }
        }
        else if (s.size() >= 2 && s[0] == '\"' && s.back() == '\"')
        {
            for (int i = 1; i < s.size() - 1; ++i)
            {
                v.push_back(s[i]);
            }
        }
        else
        {
            throw std::invalid_argument("Invalid bytearray");
        }

        if (v.size() != std::dynamic_pointer_cast<ByteArrayType>(vtype)->size)
        {
            throw std::invalid_argument("Invalid bytearray");
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

    if (s == "int" || s == "Int")
    {
        return std::make_shared<ValueType>(Int);
    }
    else if (s == "bool" || s == "Bool")
    {
        return std::make_shared<ValueType>(Bool);
    }
    else if (s == "string" || s == "String")
    {
        return std::make_shared<ValueType>(String);
    }
    else if (s == "bytearray" || s == "ByteArray")
    {
        if (args == "")
        {
            throw std::invalid_argument("Invalid bytearray size");
        }
        if (std::stoi(args) <= 0)
        {
            throw std::invalid_argument("Invalid bytearray size");
        }
        return std::make_shared<ByteArrayType>(std::stoi(args));
    }
    else
    {
        throw std::invalid_argument("Invalid type");
    }
}

std::unique_ptr<Cell> Creator::cellFromRawString(std::string s)
{
    if (s[0] == '(')
    {
        std::string type = s.substr(1, s.find(')') - 1);
        std::string value = s.substr(s.find(')') + 1);
        std::shared_ptr<ValueType> vtype = generateValueType(type);
        std::optional<std::any> val = generateValue(vtype, value);
        return generateCell(vtype, val.value());
    }
    else
    {
        if (s == "True" || s == "False" || s == "true" || s == "false")
        {
            return std::make_unique<BoolCell>(s == "True" || s == "true");
        }

        if (s.size() >= 2 && s[0] == '0' && s[1] == 'x')
        {
            std::shared_ptr<ValueType> t = std::make_shared<ByteArrayType>((s.size() - 2) / 2);
            return generateCell(t, generateValue(t, s));
        }

        bool isInt = true;
        for (int i = 0; i < s.size(); ++i)
        {
            if (s[i] == '-' && i == 0)
            {
                continue;
            }
            if (s[i] < '0' || s[i] > '9')
            {
                isInt = false;
                break;
            }
        }
        if (isInt)
        {
            return generateCell(std::make_shared<ValueType>(Int), std::stoi(s));
        }

        if (s[0] == '\"' && s.back() == '\"')
        {
            return generateCell(std::make_shared<ValueType>(String), s.substr(1, s.size() - 2));
        }

        throw std::invalid_argument("Unknown type");
    }
}

std::string Creator::stringFromValueType(std::shared_ptr<ValueType> vtype)
{
    switch (vtype->type)
    {
    case Int:
        return "int";
    case Bool:
        return "bool";
    case String:
        return "string";
    case ByteArray:
        return "bytearray[" + std::to_string(std::dynamic_pointer_cast<ByteArrayType>(vtype)->size) + "]";
    default:
        throw std::invalid_argument("Invalid type");
    }
}
