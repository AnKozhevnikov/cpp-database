#pragma once

#include "Token.h"
#include "PRNCompiler.h"
#include<vector>




class ExpressionParcer
{
    public:
    ExpressionParcer(std::string str);

    std::vector<std::unique_ptr<Cell>> get_values (const Row& cur_row);
    std::vector<std::string> updating;
    std::vector<PRN_complier> values;
};