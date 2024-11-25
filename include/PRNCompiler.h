#pragma once

#include "Row.h"
#include "ArithmParcer.h"
#include "Token.h"

class PRN_complier
{
  public:
    PRN_complier(std::string query);
    std::unique_ptr<Cell> eval(const Row &cur_row) const;

    std::vector<std::shared_ptr<Token>>& get_tokens();

  private:
    std::vector<std::shared_ptr<Token>> PRN_tokens;
};
