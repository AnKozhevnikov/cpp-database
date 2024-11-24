#pragma once

#include "Types.h"

class ColumnInfo
{
  public:
    std::shared_ptr<ValueType> vtype;
    unsigned int number;
    std::optional<std::any> baseValue;
    unsigned int attr;

    friend class DataBase;
};