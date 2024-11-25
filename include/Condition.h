#pragma once

#include "PRNCompiler.h"

class Condition : public PRN_complier
{
  public:
    Condition(std::string query) : PRN_complier(query)
    {
    }
    bool apply(const Row &cur_row);
};