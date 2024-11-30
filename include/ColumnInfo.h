#pragma once

#include "Types.h"
#include <any>
#include <optional>
#include <set>

class ColumnInfo
{
  public:
    std::shared_ptr<ValueType> vtype;
    unsigned int number;
    std::optional<std::any> baseValue;
    unsigned int attr;

    static bool cmp(const std::unique_ptr<Cell> *a, const std::unique_ptr<Cell> *b)
    {
        bool neq = std::any_cast<bool>((*a)->opNeq(*b)->getValue());
        if (neq)
        {
            return std::any_cast<bool>((*a)->opL(*b)->getValue());
        }
        else
        {
            return a < b;
        }
    }
    std::set<std::unique_ptr<Cell> *, decltype(&cmp)> data{&cmp};

    bool check(std::unique_ptr<Cell> *c)
    {
        auto it = data.find(c);
        auto left = it;
        auto right = it;
        if (it != data.begin())
        {
            left--;
            if (std::any_cast<bool>((**left)->opEq(*c)->getValue()))
            {
                return false;
            }
        }
        if (it != data.end())
        {
            right++;
            if (right != data.end() && std::any_cast<bool>((**right)->opEq(*c)->getValue()))
            {
                return false;
            }
        }

        return true;
    }

    friend class DataBase;
};
