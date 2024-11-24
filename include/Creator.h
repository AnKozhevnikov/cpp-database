#pragma once

#include <memory>
#include <optional>
#include <any>

#include "Cell.h"
#include "DataBase.h"

class Creator
{
  public:
    std::unique_ptr<Cell> generateCell(std::shared_ptr<ValueType> vtype, std::any arg);
    std::optional<std::any> generateValue(std::shared_ptr<ValueType> vtype, std::string s);
    std::shared_ptr<ValueType> generateValueType(std::string s);
};