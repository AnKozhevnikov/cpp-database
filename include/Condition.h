#pragma once
#include "ArithmParcer.h"
#include "Row.h"
#include "Token.h"
class Condition
{
  public:
    Condition(std::vector<std::shared_ptr<Token>> token_stack);
    bool apply(const Row &cur_row) const;

  private:
    std::vector<std::shared_ptr<Token>> PRN_tokens;
};