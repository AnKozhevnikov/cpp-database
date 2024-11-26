#include <ArithmParcer.h>
#include <stdexcept>

static std::map<ArithmParser::Order_type, Token::Token_types> order_to_token = {
    {ArithmParser::Order_type::Op_not, Token::Token_types::Op_not},
    {ArithmParser::Order_type::Op_mul, Token::Token_types::Op_mul},    {ArithmParser::Order_type::Op_div, Token::Token_types::Op_div},
    {ArithmParser::Order_type::Op_mod, Token::Token_types::Op_mod},    {ArithmParser::Order_type::Op_plus, Token::Token_types::Op_plus},
    {ArithmParser::Order_type::Op_minus, Token::Token_types::Op_minus},  {ArithmParser::Order_type::Op_eq, Token::Token_types::Op_eq},
    {ArithmParser::Order_type::Op_noteq, Token::Token_types::Op_noteq}, {ArithmParser::Order_type::Op_l, Token::Token_types::Op_l},
    {ArithmParser::Order_type::Op_leq, Token::Token_types::Op_leq},   {ArithmParser::Order_type::Op_g, Token::Token_types::Op_g},
    {ArithmParser::Order_type::Op_geq, Token::Token_types::Op_geq},   {ArithmParser::Order_type::Op_and, Token::Token_types::Op_and},
    {ArithmParser::Order_type::Op_xor, Token::Token_types::Op_xor},   {ArithmParser::Order_type::Op_or, Token::Token_types::Op_or}};




static std::map<Token::Token_types, int> operations_precedence = {
    {Token::Token_types::Op_not, 0}, {Token::Token_types::Op_mul, 1},   {Token::Token_types::Op_div, 1},
    {Token::Token_types::Op_mod, 1}, {Token::Token_types::Op_plus, 2},  {Token::Token_types::Op_minus, 2},
    {Token::Token_types::Op_eq, 3},  {Token::Token_types::Op_noteq, 3}, {Token::Token_types::Op_l, 3},
    {Token::Token_types::Op_leq, 3}, {Token::Token_types::Op_g, 3},     {Token::Token_types::Op_geq, 3},
    {Token::Token_types::Op_and, 4}, {Token::Token_types::Op_xor, 5},   {Token::Token_types::Op_or, 6}};

static std::map<ArithmParser::Order_type, std::string> order_to_string = {{ArithmParser::Order_type::Op_not, "!"},
    {ArithmParser::Order_type::Op_mul, "*"},    {ArithmParser::Order_type::Op_div, "//"},
    {ArithmParser::Order_type::Op_mod, "%"},    {ArithmParser::Order_type::Op_plus, "+"},
    {ArithmParser::Order_type::Op_minus, "-"},  {ArithmParser::Order_type::Op_eq, "="},
    {ArithmParser::Order_type::Op_noteq, "!="}, {ArithmParser::Order_type::Op_l, "<"},
    {ArithmParser::Order_type::Op_leq, "<="},   {ArithmParser::Order_type::Op_g, ">"},
    {ArithmParser::Order_type::Op_geq, ">="},   {ArithmParser::Order_type::Op_and, "&&"},
    {ArithmParser::Order_type::Op_xor, "^^"},   {ArithmParser::Order_type::Op_or, "||"}};

void ArithmParser::rec_parse(const std::string &str, ArithmParser::Order_type cur_token, int left, int right,
                             std::vector<std::shared_ptr<Token>> &ans)
{
    if (left > right)
        return;
    while (std::isspace(static_cast<unsigned char>(str[left])) && left <= right)
        left++;
    if (left > right)
        return ;
    while (std::isspace(static_cast<unsigned char>(str[right])))
        right--;
    
    int cur_start = left;
    int next = left;
    switch (cur_token)
    {
    case ArithmParser::Order_type::Quote: {
        int opened = 0;
        next = str.find("\"", left);
        while (next <= right && next != std::string::npos)
        {
            if (opened == 0)
            {
                rec_parse(str, static_cast<ArithmParser::Order_type>(cur_token + 1), cur_start, next - 1, ans);
            }
            else
            {
                ans.push_back(std::make_shared<StrToken>(str.substr(cur_start - 1, next - cur_start + 2)));
            }
            opened ^= 1;
            cur_start = next + 1;
            next = str.find("\"", cur_start);
        }
        if (opened == 1)
        {
            throw std::runtime_error("Arithm_parser:: No matching \" was found");
        }
        break;
    }
    case ArithmParser::Order_type::Par: {
        next = str.find("(", left);
        while (next <= right && next != std::string::npos)
        {
            rec_parse(str, static_cast<ArithmParser::Order_type>(cur_token + 1), cur_start, next - 1, ans);
            ans.push_back(std::make_shared<OpToken>(Token::Token_types::Par_left));
            cur_start = next + 1;
            int balance = 0;
            for (int cur_pos = cur_start; cur_pos < right; cur_pos++)
            {
                if (str[cur_pos] == '(')
                {
                    balance++;
                }
                else if (str[cur_pos] == ')')
                {
                    if (balance == 0)
                    {
                        next = cur_pos;
                        break;
                    }
                    else
                    {
                        balance--;
                    }
                }
            }
            if (next < cur_start)
            {
                throw std::runtime_error("Arithm_parser:: No matching ) was found");
            }
            rec_parse(str, static_cast<ArithmParser::Order_type>(cur_token), cur_start, next - 1, ans);
            ans.push_back(std::make_shared<OpToken>(Token::Token_types::Par_right));
            cur_start = next + 1;
            next = str.find("(", cur_start);
        }
        break;
    }
    case ArithmParser::Order_type::Op_abs: {
        int opened = 0;
        next = str.find("|", left);
        while (next <= right && next != std::string::npos)
        {
            if (opened == 0)
            {
                rec_parse(str, static_cast<ArithmParser::Order_type>(cur_token + 1), cur_start, next - 1, ans);
            }
            else
            {
                ans.push_back(std::make_shared<OpToken>(Token::Token_types::Op_abs));
                ans.push_back(std::make_shared<OpToken>(Token::Token_types::Par_left));
                rec_parse(str, static_cast<ArithmParser::Order_type>(cur_token + 1), cur_start, next - 1, ans);
                ans.push_back(std::make_shared<OpToken>(Token::Token_types::Par_right));
            }
            opened ^= 1;
            cur_start = next + 1;
            next = str.find("|", cur_start);
        }
        if (opened == 1)
        {
            throw std::runtime_error("Arithm_parser:: No matching | was found");
        }
        break;
    }
    case ArithmParser::Order_type::Var: {
        while (std::isspace(static_cast<unsigned char>(str[left])))
            left++;
        while (std::isspace(static_cast<unsigned char>(str[right])))
            right--;
        ans.push_back(std::make_shared<StrToken>(str.substr(left, right - left + 1)));
        return;
    }
    default: {
        next = str.find(order_to_string[cur_token], left);
        auto p = order_to_string[cur_token];
        while (next <= right && next != std::string::npos)
        {
            rec_parse(str, static_cast<ArithmParser::Order_type>(cur_token + 1), cur_start, next - 1, ans);
            ans.push_back(std::make_shared<OpToken>(order_to_token[cur_token]));
            cur_start = next + 1;
            next = str.find(order_to_string[cur_token], cur_start);
        }
        break;
    }
    }
    rec_parse(str, static_cast<ArithmParser::Order_type>(cur_token + 1), cur_start, right, ans);
}
std::vector<std::shared_ptr<Token>> ArithmParser::arithm_parse(std::string origin_str)
{

    std::vector<std::shared_ptr<Token>> input;
    rec_parse(origin_str, ArithmParser::Order_type::Quote, 0, origin_str.length() - 1, input);
    std::vector<std::shared_ptr<Token>> op_stack;
    std::vector<std::shared_ptr<Token>> output;

    // https://en.wikipedia.org/wiki/Shunting_yard_algorithm
    for (std::shared_ptr<Token> &cur_token : input)
    {
        if (cur_token->type == Token::Token_types::String)
        {
            output.emplace_back(cur_token);
        }
        else if (cur_token->type == Token::Token_types::Par_left)
        {
            op_stack.emplace_back(cur_token);
        }
        else if (cur_token->type == Token::Token_types::Par_right)
        {
            while (!op_stack.empty() && op_stack.back()->type != Token::Token_types::Par_left)
            {
                output.emplace_back(op_stack.back());
                op_stack.pop_back();
            }
        }
        else
        {
            while (!op_stack.empty() &&
                   operations_precedence[cur_token->type] >= operations_precedence[op_stack.back()->type])
            {
                output.emplace_back(op_stack.back());
                op_stack.pop_back();
            }
            op_stack.emplace_back(cur_token);
        }
    }
    while (!op_stack.empty())
    {
        output.emplace_back(op_stack.back());
        op_stack.pop_back();
    }
    return output;
}