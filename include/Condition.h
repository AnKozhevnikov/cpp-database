#pragma once
#include "ArithmParcer.h"
#include "Row.h"
#include "Token.h"
class Condition
{
  public:
    Condition(std::string query);
    bool apply(const Row &cur_row) const;

  private:
    std::vector<std::shared_ptr<Token>> PRN_tokens;
};