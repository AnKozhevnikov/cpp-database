#pragma once

#include <map>
#include <string>
#include <vector>
#include <memory>

#include "Cell.h"
#include "ColumnInfo.h"
#include "Creator.h"

class Row
{
  public:
    Row(std::map<std::string, ColumnInfo> *m) : columns(m), sz(0) {}

    int getPos(std::string name) const;

    unsigned int sz;
    std::map<std::string, ColumnInfo> *columns;
    std::vector<std::unique_ptr<Cell>> v;

    template <typename T>
    T get(std::string name) const
    {
        return std::any_cast<T>(v[getPos(name)]->getValue());
    }

    Row(const Row &other) = delete;                 // Disable copy constructor
    Row(Row &&other) noexcept = default;            // Enable move constructor
    Row &operator=(const Row &other) = delete;      // Disable copy assignment
    Row &operator=(Row &&other) noexcept = default; // Enable move assignment
};