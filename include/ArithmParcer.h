#pragma once

#include "Token.h"
#include <vector>
#include <map>
class ArithmParser
{

  public:
    ArithmParser() = delete;
    enum Order_type
    {
        Quote,
        Par,
        Op_abs,
        Op_eq,
        Op_noteq,
        Op_l,
        Op_leq,
        Op_g,
        Op_geq,
        Op_and,
        Op_xor,
        Op_or,
        Op_plus,
        Op_minus,
        Op_mul,
        Op_div,
        Op_mod,
        Op_not,
        Var
    };
    static void rec_parse(const std::string& str, Order_type cur_token, int left, int right, std::vector<std::shared_ptr<Token>>& ans);
    static std::vector<std::shared_ptr<Token>> arithm_parse(std::string origin_str);
    
};

