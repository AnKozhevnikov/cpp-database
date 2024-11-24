#include "Condition.h"
#include "Cell.h"
#include <vector>
#include <stdexcept>

Condition::Condition(std::vector<std::shared_ptr<Token>> token_stack)  : PRN_tokens(token_stack)
{
    for (int i = 0; i < PRN_tokens.size(); i++)
    {
        if (PRN_tokens[i]->type != Token::Token_types::String)
        {
            PRN_tokens[i] = OpTokenCreator::generate_op(PRN_tokens[i]->type);
        }
    }
}
bool Condition::apply(const Row &cur_row) const
{
    if (PRN_tokens.empty())
        return true;
    std::vector<std::shared_ptr<Token>> cur_stack = PRN_tokens;
    for (int i = 0; i < cur_stack.size(); i++)
    {
        if (cur_stack[i]->type == Token::Token_types::String)
        {
            cur_stack[i] == std::make_shared<VarToken>(cur_row, cur_stack[i]);
        }
    }
    while (cur_stack.size() != 1 && cur_stack.back()->type != Token::Token_types::Variable)
    {
        cur_stack.emplace_back(std::dynamic_pointer_cast<OpToken>(cur_stack.back())->apply(cur_stack));
    }
    if (cur_stack.size() != 1)
    {
        throw std::runtime_error("Condition: stack size is not 1");
    }

    return dynamic_cast<const BoolCell&>(*std::dynamic_pointer_cast<VarToken>(cur_stack.back())->value).value;

}
