#pragma once

#include <memory>
#include <optional>
#include <any>

#include "Cell.h"
#include "DataBase.h"

class Creator
{
  public:
    static std::unique_ptr<Cell> generateCell(std::shared_ptr<ValueType> vtype, std::any arg);
    static std::optional<std::any> generateValue(std::shared_ptr<ValueType> vtype, std::string s);
    static std::shared_ptr<ValueType> generateValueType(std::string s);
    static std::unique_ptr<Cell> cellFromRawString(std::string s);
    static std::string stringFromValueType(std::shared_ptr<ValueType> vtype);
};