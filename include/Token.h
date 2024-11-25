#pragma once

#include "Cell.h"
#include "Row.h"
#include "Creator.h"

class Token
{
  public:
    enum Token_types
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
    virtual ~Token() = default;
};

class StrToken : public Token
{
  public:
    StrToken(std::string str) : Token(Token::Token_types::String), value(str)
    {
    }
    std::string value;
};

class VarToken : public Token
{
  public:
    VarToken(const Row &associated, std::shared_ptr<StrToken> original);
    VarToken(std::unique_ptr<Cell> val) : Token(Token::Token_types::Variable), value(val->clone())
    {
    }
    std::unique_ptr<Cell> value;
};

class OpToken : public Token
{
  public:
    OpToken(Token::Token_types v) : Token(v)
    {
    }
    virtual std::unique_ptr<Cell> apply(std::vector<std::shared_ptr<Token>> &); 
};

class NotOpToken : public OpToken
{
  public:
    NotOpToken() : OpToken(Token::Token_types::Op_not)
    {
    }
    std::unique_ptr<Cell> apply(std::vector<std::shared_ptr<Token>> &stack);
};

class MulOpToken : public OpToken
{
  public:
    MulOpToken() : OpToken(Token::Token_types::Op_mul)
    {
    }
    std::unique_ptr<Cell> apply(std::vector<std::shared_ptr<Token>> &stack);
};
class DivOpToken : public OpToken
{
  public:
    DivOpToken() : OpToken(Token::Token_types::Op_div)
    {
    }
    std::unique_ptr<Cell> apply(std::vector<std::shared_ptr<Token>> &stack);
};
class ModOpToken : public OpToken
{
  public:
    ModOpToken() : OpToken(Token::Token_types::Op_mod)
    {
    }
    std::unique_ptr<Cell> apply(std::vector<std::shared_ptr<Token>> &stack);
};
class PlusOpToken : public OpToken
{
  public:
    PlusOpToken() : OpToken(Token::Token_types::Op_plus)
    {
    }
    std::unique_ptr<Cell> apply(std::vector<std::shared_ptr<Token>> &stack);
};
class MinusOpToken : public OpToken
{
  public:
    MinusOpToken() : OpToken(Token::Token_types::Op_minus)
    {
    }
    std::unique_ptr<Cell> apply(std::vector<std::shared_ptr<Token>> &stack);
};
class AbsOpToken : public OpToken
{
  public:
    AbsOpToken() : OpToken(Token::Token_types::Op_abs)
    {
    }
    std::unique_ptr<Cell> apply(std::vector<std::shared_ptr<Token>> &stack);
};
class EqOpToken : public OpToken
{
  public:
    EqOpToken() : OpToken(Token::Token_types::Op_eq)
    {
    }
    std::unique_ptr<Cell> apply(std::vector<std::shared_ptr<Token>> &stack);
};
class NoteqOpToken : public OpToken
{
  public:
    NoteqOpToken() : OpToken(Token::Token_types::Op_noteq)
    {
    }
    std::unique_ptr<Cell> apply(std::vector<std::shared_ptr<Token>> &stack);
};
class LOpToken : public OpToken
{
  public:
    LOpToken() : OpToken(Token::Token_types::Op_l)
    {
    }
    std::unique_ptr<Cell> apply(std::vector<std::shared_ptr<Token>> &stack);
};
class LeqOpToken : public OpToken
{
  public:
    LeqOpToken() : OpToken(Token::Token_types::Op_leq)
    {
    }
    std::unique_ptr<Cell> apply(std::vector<std::shared_ptr<Token>> &stack);
};
class GOpToken : public OpToken
{
  public:
    GOpToken() : OpToken(Token::Token_types::Op_g)
    {
    }
    std::unique_ptr<Cell> apply(std::vector<std::shared_ptr<Token>> &stack);
};
class GeqOpToken : public OpToken
{
  public:
    GeqOpToken() : OpToken(Token::Token_types::Op_geq)
    {
    }
    std::unique_ptr<Cell> apply(std::vector<std::shared_ptr<Token>> &stack);
};
class AndOpToken : public OpToken
{
  public:
    AndOpToken() : OpToken(Token::Token_types::Op_and)
    {
    }
    std::unique_ptr<Cell> apply(std::vector<std::shared_ptr<Token>> &stack);
};
class XorOpToken : public OpToken
{
  public:
    XorOpToken() : OpToken(Token::Token_types::Op_xor)
    {
    }
    std::unique_ptr<Cell> apply(std::vector<std::shared_ptr<Token>> &stack);
};
class OrOpToken : public OpToken
{
  public:
    OrOpToken() : OpToken(Token::Token_types::Op_or)
    {
    }
    std::unique_ptr<Cell> apply(std::vector<std::shared_ptr<Token>> &stack);
};

class OpTokenCreator
{
  public:
    OpTokenCreator() = delete;
    static std::shared_ptr<OpToken> generate_op(Token::Token_types val);
};