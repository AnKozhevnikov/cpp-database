#include "PRNCompiler.h"
#include "ArithmParcer.h"
#include "Cell.h"
#include <stdexcept>
#include <vector>

PRN_complier::PRN_complier(std::string query)
{
    PRN_tokens = ArithmParser::arithm_parse(query);
    for (int i = 0; i < PRN_tokens.size(); i++)
    {
        if (PRN_tokens[i]->type != Token::Token_types::String)
        {
            PRN_tokens[i] = OpTokenCreator::generate_op(PRN_tokens[i]->type);
        }
    }
}
std::vector<std::shared_ptr<Token>> &PRN_complier::get_tokens()
{
    return PRN_tokens;
}

std::unique_ptr<Cell> PRN_complier::eval(const Row &cur_row) const
{
    if (PRN_tokens.empty())
        return nullptr;
    std::vector<std::shared_ptr<Token>> cur_stack;

    for (auto i : PRN_tokens)
    {
        if (i->type == Token::Token_types::String)
        {
            cur_stack.emplace_back(std::make_shared<VarToken>(cur_row, std::dynamic_pointer_cast<StrToken>(i)));
        }
        else
        {
            cur_stack.emplace_back(i);
            cur_stack.push_back(
                std::make_shared<VarToken>(std::dynamic_pointer_cast<OpToken>(cur_stack.back())->apply(cur_stack)));
        }
    }

    if (cur_stack.size() != 1)
    {
        throw std::runtime_error("Condition: stack size is not 1");
    }

    return std::dynamic_pointer_cast<VarToken>(cur_stack.back())->value->clone();
}
