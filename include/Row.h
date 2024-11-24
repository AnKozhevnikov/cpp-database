#pragma once

#include "Condition.h"

class Row
{
  public:
    Row() = default;

    bool fits(Condition cond);

    unsigned int sz;
    std::vector<std::unique_ptr<Cell>> v;

    Row(const Row &other) = delete;                 // Disable copy constructor
    Row(Row &&other) noexcept = default;            // Enable move constructor
    Row &operator=(const Row &other) = delete;      // Disable copy assignment
    Row &operator=(Row &&other) noexcept = default; // Enable move assignment
};