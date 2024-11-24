#pragma once

#include "Cell.h"
#include "Row.h"
#include <algorithm>
#include <cctype>
#include <map>
#include <memory>
#include <stdexcept>
#include <vector>

/*
So, we're gonna have 2 types of parsers

1. Arithmetic string -> Reverse polish with tokens  :  string -> vector<Tokens>
2. Reverse polish -> applying all operations

*/

class Token
{
  public:
    enum class Token_types
    {
        Variable,
        String,
        Par_left,
        Par_right,
        Op_not,
        Op_mul,
        Op_div,
        Op_mod,
        Op_plus,
        Op_minus,
        Op_abs,
        Op_eq,
        Op_noteq,
        Op_l,
        Op_leq,
        Op_g,
        Op_geq,
        Op_and,
        Op_xor,
        Op_or
    };
    Token_types type;
    Token(Token::Token_types val) : type(val)
    {
    }
};
class StrToken : public Token
{
  public:
    StrToken(std::string str) : Token(Token::Token_types::String), value(str)
    {
    }
    std::string value;
};

class OpToken : public Token
{
  public:
    OpToken(Token::Token_types v) : Token(v)
    {
    }
    virtual std::unique_ptr<Cell> apply(const std::vector<std::shared_ptr<Token>> &) = 0;
};

class VarToken : public Token
{
  public:
    VarToken(const Row &associated, std::shared_ptr<StrToken> original) : Token(Token::Token_types::Variable)
    {
        int pos = associated.getPos(original->value);
        if (pos == -1)
        {
            value = std::make_unique<Cell>(original->value);
        }
        else
        {
            value = associated.v[pos]->clone();
        }
    }
    VarToken(std::unique_ptr<Cell> val) : Token(Token::Token_types::Variable)
    {
        value = val->clone();
    }
    std::unique_ptr<Cell> value;
};

class OpTokenCreator
{
  public:
    OpTokenCreator() = delete;
    static std::shared_ptr<OpToken> generate_op(Token::Token_types val)
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
};

class NotOpToken : public OpToken
{
    NotOpToken() : OpToken(Token::Token_types::Op_not)
    {
    }
    // TODO: is it correct
    std::unique_ptr<Cell> apply(std::vector<std::shared_ptr<Token>> &stack)
    {
        std::unique_ptr<Cell> var = std::dynamic_pointer_cast<VarToken>(stack.back())->value->clone();
        stack.pop_back();
        return var->opNot();
    }
};

class MulOpToken : public OpToken
{
    MulOpToken() : OpToken(Token::Token_types::Op_mul)
    {
    }
    // TODO: is it correct
    std::unique_ptr<Cell> apply(std::vector<std::shared_ptr<Token>> &stack)
    {
        std::unique_ptr<Cell> var1 = std::dynamic_pointer_cast<VarToken>(stack.back())->value->clone();
        stack.pop_back();
        std::unique_ptr<Cell> var2 = std::dynamic_pointer_cast<VarToken>(stack.back())->value->clone();
        stack.pop_back();
        return var1->opMult(var2);
    }
};
class DivOpToken : public OpToken
{
    DivOpToken() : OpToken(Token::Token_types::Op_div)
    {
    }
    // TODO: is it correct
    std::unique_ptr<Cell> apply(std::vector<std::shared_ptr<Token>> &stack)
    {
        std::unique_ptr<Cell> var1 = std::dynamic_pointer_cast<VarToken>(stack.back())->value->clone();
        stack.pop_back();
        std::unique_ptr<Cell> var2 = std::dynamic_pointer_cast<VarToken>(stack.back())->value->clone();
        stack.pop_back();
        return var1->opDiv(var2);
    }
};
class ModOpToken : public OpToken
{
    ModOpToken() : OpToken(Token::Token_types::Op_mod)
    {
    }
    // TODO: is it correct
    std::unique_ptr<Cell> apply(std::vector<std::shared_ptr<Token>> &stack)
    {
        std::unique_ptr<Cell> var1 = std::dynamic_pointer_cast<VarToken>(stack.back())->value->clone();
        stack.pop_back();
        std::unique_ptr<Cell> var2 = std::dynamic_pointer_cast<VarToken>(stack.back())->value->clone();
        stack.pop_back();
        return var1->opMod(var2);
    }
};
class PlusOpToken : public OpToken
{
    PlusOpToken() : OpToken(Token::Token_types::Op_plus)
    {
    }
    // TODO: is it correct
    std::unique_ptr<Cell> apply(std::vector<std::shared_ptr<Token>> &stack)
    {
        std::unique_ptr<Cell> var1 = std::dynamic_pointer_cast<VarToken>(stack.back())->value->clone();
        stack.pop_back();
        std::unique_ptr<Cell> var2 = std::dynamic_pointer_cast<VarToken>(stack.back())->value->clone();
        stack.pop_back();
        return var1->opPlus(var2);
    }
};
class MinusOpToken : public OpToken
{
    MinusOpToken() : OpToken(Token::Token_types::Op_minus)
    {
    }
    // TODO: is it correct
    std::unique_ptr<Cell> apply(std::vector<std::shared_ptr<Token>> &stack)
    {
        std::unique_ptr<Cell> var1 = std::dynamic_pointer_cast<VarToken>(stack.back())->value->clone();
        stack.pop_back();
        std::unique_ptr<Cell> var2 = std::dynamic_pointer_cast<VarToken>(stack.back())->value->clone();
        stack.pop_back();
        return var1->opMinus(var2);
    }
};
class AbsOpToken : public OpToken
{
    AbsOpToken() : OpToken(Token::Token_types::Op_abs)
    {
    }
    // TODO: is it correct
    std::unique_ptr<Cell> apply(std::vector<std::shared_ptr<Token>> &stack)
    {
        std::unique_ptr<Cell> var1 = std::dynamic_pointer_cast<VarToken>(stack.back())->value->clone();
        stack.pop_back();
        return var1->opAbs();
    }
};
class EqOpToken : public OpToken
{
    EqOpToken() : OpToken(Token::Token_types::Op_eq)
    {
    }
    // TODO: is it correct
    std::unique_ptr<Cell> apply(std::vector<std::shared_ptr<Token>> &stack)
    {
        std::unique_ptr<Cell> var1 = std::dynamic_pointer_cast<VarToken>(stack.back())->value->clone();
        stack.pop_back();
        std::unique_ptr<Cell> var2 = std::dynamic_pointer_cast<VarToken>(stack.back())->value->clone();
        stack.pop_back();
        return var1->opEq(var2);
    }
};

class NoteqOpToken : public OpToken
{
    NoteqOpToken() : OpToken(Token::Token_types::Op_noteq)
    {
    }
    // TODO: is it correct
    std::unique_ptr<Cell> apply(std::vector<std::shared_ptr<Token>> &stack)
    {
        std::unique_ptr<Cell> var1 = std::dynamic_pointer_cast<VarToken>(stack.back())->value->clone();
        stack.pop_back();
        std::unique_ptr<Cell> var2 = std::dynamic_pointer_cast<VarToken>(stack.back())->value->clone();
        stack.pop_back();
        return var1->opNeq(var2);
    }
};

class LOpToken : public OpToken
{
    LOpToken() : OpToken(Token::Token_types::Op_l)
    {
    }
    // TODO: is it correct
    std::unique_ptr<Cell> apply(std::vector<std::shared_ptr<Token>> &stack)
    {
        std::unique_ptr<Cell> var1 = std::dynamic_pointer_cast<VarToken>(stack.back())->value->clone();
        stack.pop_back();
        std::unique_ptr<Cell> var2 = std::dynamic_pointer_cast<VarToken>(stack.back())->value->clone();
        stack.pop_back();
        return var1->opL(var2);
    }
};
class LeqOpToken : public OpToken
{
    LeqOpToken() : OpToken(Token::Token_types::Op_leq)
    {
    }
    // TODO: is it correct
    std::unique_ptr<Cell> apply(std::vector<std::shared_ptr<Token>> &stack)
    {
        std::unique_ptr<Cell> var1 = std::dynamic_pointer_cast<VarToken>(stack.back())->value->clone();
        stack.pop_back();
        std::unique_ptr<Cell> var2 = std::dynamic_pointer_cast<VarToken>(stack.back())->value->clone();
        stack.pop_back();
        return var1->opLeq(var2);
    }
};
class GOpToken : public OpToken
{
    GOpToken() : OpToken(Token::Token_types::Op_g)
    {
    }
    // TODO: is it correct
    std::unique_ptr<Cell> apply(std::vector<std::shared_ptr<Token>> &stack)
    {
        std::unique_ptr<Cell> var1 = std::dynamic_pointer_cast<VarToken>(stack.back())->value->clone();
        stack.pop_back();
        std::unique_ptr<Cell> var2 = std::dynamic_pointer_cast<VarToken>(stack.back())->value->clone();
        stack.pop_back();
        return var1->opG(var2);
    }
};

class GeqOpToken : public OpToken
{
    GeqOpToken() : OpToken(Token::Token_types::Op_geq)
    {
    }
    // TODO: is it correct
    std::unique_ptr<Cell> apply(std::vector<std::shared_ptr<Token>> &stack)
    {
        std::unique_ptr<Cell> var1 = std::dynamic_pointer_cast<VarToken>(stack.back())->value->clone();
        stack.pop_back();
        std::unique_ptr<Cell> var2 = std::dynamic_pointer_cast<VarToken>(stack.back())->value->clone();
        stack.pop_back();
        return var1->opGeq(var2);
    }
};
class AndOpToken : public OpToken
{
    AndOpToken() : OpToken(Token::Token_types::Op_and)
    {
    }
    // TODO: is it correct
    std::unique_ptr<Cell> apply(std::vector<std::shared_ptr<Token>> &stack)
    {
        std::unique_ptr<Cell> var1 = std::dynamic_pointer_cast<VarToken>(stack.back())->value->clone();
        stack.pop_back();
        std::unique_ptr<Cell> var2 = std::dynamic_pointer_cast<VarToken>(stack.back())->value->clone();
        stack.pop_back();
        return var1->opAnd(var2);
    }
};
class XorOpToken : public OpToken
{
    XorOpToken() : OpToken(Token::Token_types::Op_xor)
    {
    }
    // TODO: is it correct
    std::unique_ptr<Cell> apply(std::vector<std::shared_ptr<Token>> &stack)
    {
        std::unique_ptr<Cell> var1 = std::dynamic_pointer_cast<VarToken>(stack.back())->value->clone();
        stack.pop_back();
        std::unique_ptr<Cell> var2 = std::dynamic_pointer_cast<VarToken>(stack.back())->value->clone();
        stack.pop_back();
        return var1->opXor(var2);
    }
};
class OrOpToken : public OpToken
{
    OrOpToken() : OpToken(Token::Token_types::Op_or)
    {
    }
    // TODO: is it correct
    std::unique_ptr<Cell> apply(std::vector<std::shared_ptr<Token>> &stack)
    {
        std::unique_ptr<Cell> var1 = std::dynamic_pointer_cast<VarToken>(stack.back())->value->clone();
        stack.pop_back();
        std::unique_ptr<Cell> var2 = std::dynamic_pointer_cast<VarToken>(stack.back())->value->clone();
        stack.pop_back();
        return var1->opOr(var2);
    }
};