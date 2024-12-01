#pragma once

#include "Row.h"
#include "Types.h"
#include <any>
#include <optional>
#include <set>

class Row;

class ColumnInfo
{
  public:
    std::shared_ptr<ValueType> vtype;
    unsigned int number;
    std::optional<std::any> baseValue;
    unsigned int attr;

    static bool cmp(const std::unique_ptr<Cell> *a, const std::unique_ptr<Cell> *b)
    {
        return std::any_cast<bool>((*a)->opL(*b)->getValue());
    }
    std::map<std::unique_ptr<Cell> *, std::set<Row *>, decltype(&cmp)> data{&cmp};

    bool check(std::unique_ptr<Cell> *c)
    {
        return data[c].size() == 1;
    }

    friend class DataBase;
};
