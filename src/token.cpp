#include <Creator.h>
#include <Token.h>
#include <algorithm>
#include <cctype>
#include <map>
#include <memory>
#include <stdexcept>
#include <vector>

VarToken::VarToken(const Row &associated, std::shared_ptr<StrToken> original) : Token(Token::Token_types::Variable)
{
    int pos = associated.getPos(original->value);
    if (pos == -1)
    {
        value = Creator::cellFromRawString(original->value);
    }
    else
    {
        value = associated.v[pos]->clone();
    }
}

std::unique_ptr<Cell> OpToken::apply(std::vector<std::shared_ptr<Token>> &)
{
    throw std::runtime_error("OpToken: apply is not implemented");
}

std::unique_ptr<Cell> NotOpToken::apply(std::vector<std::shared_ptr<Token>> &stack)
{
    stack.pop_back();
    std::unique_ptr<Cell> var = std::dynamic_pointer_cast<VarToken>(stack.back())->value->clone();
    stack.pop_back();
    return var->opNot();
}

std::unique_ptr<Cell> MulOpToken::apply(std::vector<std::shared_ptr<Token>> &stack)
{
    stack.pop_back();
    std::unique_ptr<Cell> var1 = std::dynamic_pointer_cast<VarToken>(stack.back())->value->clone();
    stack.pop_back();
    std::unique_ptr<Cell> var2 = std::dynamic_pointer_cast<VarToken>(stack.back())->value->clone();
    stack.pop_back();
    return var2->opMult(var1);
}

std::unique_ptr<Cell> DivOpToken::apply(std::vector<std::shared_ptr<Token>> &stack)
{
    stack.pop_back();
    std::unique_ptr<Cell> var1 = std::dynamic_pointer_cast<VarToken>(stack.back())->value->clone();
    stack.pop_back();
    std::unique_ptr<Cell> var2 = std::dynamic_pointer_cast<VarToken>(stack.back())->value->clone();
    stack.pop_back();
    return var2->opDiv(var1);
}

std::unique_ptr<Cell> ModOpToken::apply(std::vector<std::shared_ptr<Token>> &stack)
{
    stack.pop_back();
    std::unique_ptr<Cell> var1 = std::dynamic_pointer_cast<VarToken>(stack.back())->value->clone();
    stack.pop_back();
    std::unique_ptr<Cell> var2 = std::dynamic_pointer_cast<VarToken>(stack.back())->value->clone();
    stack.pop_back();
    return var2->opMod(var1);
}

std::unique_ptr<Cell> PlusOpToken::apply(std::vector<std::shared_ptr<Token>> &stack)
{
    stack.pop_back();
    std::unique_ptr<Cell> var1 = std::dynamic_pointer_cast<VarToken>(stack.back())->value->clone();
    stack.pop_back();
    std::unique_ptr<Cell> var2 = std::dynamic_pointer_cast<VarToken>(stack.back())->value->clone();
    stack.pop_back();
    return var2->opPlus(var1);
}

std::unique_ptr<Cell> MinusOpToken::apply(std::vector<std::shared_ptr<Token>> &stack)
{
    stack.pop_back();
    std::unique_ptr<Cell> var1 = std::dynamic_pointer_cast<VarToken>(stack.back())->value->clone();
    stack.pop_back();
    std::unique_ptr<Cell> var2 = std::dynamic_pointer_cast<VarToken>(stack.back())->value->clone();
    stack.pop_back();
    return var2->opMinus(var1);
}

std::unique_ptr<Cell> AbsOpToken::apply(std::vector<std::shared_ptr<Token>> &stack)
{
    stack.pop_back();
    std::unique_ptr<Cell> var1 = std::dynamic_pointer_cast<VarToken>(stack.back())->value->clone();
    stack.pop_back();
    return var1->opAbs();
}

std::unique_ptr<Cell> EqOpToken::apply(std::vector<std::shared_ptr<Token>> &stack)
{
    stack.pop_back();
    std::unique_ptr<Cell> var1 = std::dynamic_pointer_cast<VarToken>(stack.back())->value->clone();
    stack.pop_back();
    std::unique_ptr<Cell> var2 = std::dynamic_pointer_cast<VarToken>(stack.back())->value->clone();
    stack.pop_back();
    return var2->opEq(var1);
}

std::unique_ptr<Cell> NoteqOpToken::apply(std::vector<std::shared_ptr<Token>> &stack)
{
    stack.pop_back();
    std::unique_ptr<Cell> var1 = std::dynamic_pointer_cast<VarToken>(stack.back())->value->clone();
    stack.pop_back();
    std::unique_ptr<Cell> var2 = std::dynamic_pointer_cast<VarToken>(stack.back())->value->clone();
    stack.pop_back();
    return var2->opNeq(var1);
}

std::unique_ptr<Cell> LOpToken::apply(std::vector<std::shared_ptr<Token>> &stack)
{
    stack.pop_back();
    std::unique_ptr<Cell> var1 = std::dynamic_pointer_cast<VarToken>(stack.back())->value->clone();
    stack.pop_back();
    std::unique_ptr<Cell> var2 = std::dynamic_pointer_cast<VarToken>(stack.back())->value->clone();
    stack.pop_back();
    return var2->opL(var1);
}

std::unique_ptr<Cell> LeqOpToken::apply(std::vector<std::shared_ptr<Token>> &stack)
{
    stack.pop_back();
    std::unique_ptr<Cell> var1 = std::dynamic_pointer_cast<VarToken>(stack.back())->value->clone();
    stack.pop_back();
    std::unique_ptr<Cell> var2 = std::dynamic_pointer_cast<VarToken>(stack.back())->value->clone();
    stack.pop_back();
    return var2->opLeq(var1);
}

std::unique_ptr<Cell> GOpToken::apply(std::vector<std::shared_ptr<Token>> &stack)
{
    stack.pop_back();
    std::unique_ptr<Cell> var1 = std::dynamic_pointer_cast<VarToken>(stack.back())->value->clone();
    stack.pop_back();
    std::unique_ptr<Cell> var2 = std::dynamic_pointer_cast<VarToken>(stack.back())->value->clone();
    stack.pop_back();
    return var2->opG(var1);
}

std::unique_ptr<Cell> GeqOpToken::apply(std::vector<std::shared_ptr<Token>> &stack)
{
    stack.pop_back();
    std::unique_ptr<Cell> var1 = std::dynamic_pointer_cast<VarToken>(stack.back())->value->clone();
    stack.pop_back();
    std::unique_ptr<Cell> var2 = std::dynamic_pointer_cast<VarToken>(stack.back())->value->clone();
    stack.pop_back();
    return var2->opGeq(var1);
}

std::unique_ptr<Cell> AndOpToken::apply(std::vector<std::shared_ptr<Token>> &stack)
{
    stack.pop_back();
    std::unique_ptr<Cell> var1 = std::dynamic_pointer_cast<VarToken>(stack.back())->value->clone();
    stack.pop_back();
    std::unique_ptr<Cell> var2 = std::dynamic_pointer_cast<VarToken>(stack.back())->value->clone();
    stack.pop_back();
    return var2->opAnd(var1);
}

std::unique_ptr<Cell> XorOpToken::apply(std::vector<std::shared_ptr<Token>> &stack)
{
    stack.pop_back();
    std::unique_ptr<Cell> var1 = std::dynamic_pointer_cast<VarToken>(stack.back())->value->clone();
    stack.pop_back();
    std::unique_ptr<Cell> var2 = std::dynamic_pointer_cast<VarToken>(stack.back())->value->clone();
    stack.pop_back();
    return var2->opXor(var1);
}

std::unique_ptr<Cell> OrOpToken::apply(std::vector<std::shared_ptr<Token>> &stack)
{
    stack.pop_back();
    std::unique_ptr<Cell> var1 = std::dynamic_pointer_cast<VarToken>(stack.back())->value->clone();
    stack.pop_back();
    std::unique_ptr<Cell> var2 = std::dynamic_pointer_cast<VarToken>(stack.back())->value->clone();
    stack.pop_back();
    return var2->opOr(var1);
}

std::shared_ptr<OpToken> OpTokenCreator::generate_op(Token::Token_types val)
{
    switch (val)
    {
    case Token::Token_types::Op_not:
        return std::make_shared<NotOpToken>();
    case Token::Token_types::Op_mul:
        return std::make_shared<MulOpToken>();
    case Token::Token_types::Op_div:
        return std::make_shared<DivOpToken>();
    case Token::Token_types::Op_mod:
        return std::make_shared<ModOpToken>();
    case Token::Token_types::Op_plus:
        return std::make_shared<PlusOpToken>();
    case Token::Token_types::Op_minus:
        return std::make_shared<MinusOpToken>();
    case Token::Token_types::Op_abs:
        return std::make_shared<AbsOpToken>();
    case Token::Token_types::Op_eq:
        return std::make_shared<EqOpToken>();
    case Token::Token_types::Op_noteq:
        return std::make_shared<NoteqOpToken>();
    case Token::Token_types::Op_l:
        return std::make_shared<LOpToken>();
    case Token::Token_types::Op_leq:
        return std::make_shared<LeqOpToken>();
    case Token::Token_types::Op_g:
        return std::make_shared<GOpToken>();
    case Token::Token_types::Op_geq:
        return std::make_shared<GeqOpToken>();
    case Token::Token_types::Op_and:
        return std::make_shared<AndOpToken>();
    case Token::Token_types::Op_xor:
        return std::make_shared<XorOpToken>();
    case Token::Token_types::Op_or:
        return std::make_shared<OrOpToken>();

    default:
        throw std::runtime_error("OpTokenCreator: tried to make non-op token");
    }
}