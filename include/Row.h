#pragma once

#include "Condition.h"
#include <map>
#include <string>
#include <vector>
#include <memory>

#include "Cell.h"
#include "ColumnInfo.h"

class Row
{
  public:
    Row(std::map<std::string, ColumnInfo> &m) : columns(m), sz(0) {}

    int getPos(std::string name);

    unsigned int sz;
    std::map<std::string, ColumnInfo> &columns;
    std::vector<std::unique_ptr<Cell>> v;

    Row(const Row &other) = delete;                 // Disable copy constructor
    Row(Row &&other) noexcept = default;            // Enable move constructor
    Row &operator=(const Row &other) = delete;      // Disable copy assignment
    Row &operator=(Row &&other) noexcept = default; // Enable move assignment
};