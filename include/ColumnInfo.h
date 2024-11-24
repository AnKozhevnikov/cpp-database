#pragma once

#include "Types.h"
#include <any>
#include <optional>

class ColumnInfo
{
  public:
    std::shared_ptr<ValueType> vtype;
    unsigned int number;
    std::optional<std::any> baseValue;
    unsigned int attr;

    friend class DataBase;
};