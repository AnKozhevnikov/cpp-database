#include <DataBase.h>
#include <algorithm>
#include <cctype>
#include <map>
#include <stdexcept>
#include <vector>
/*
So, we're gonna have 2 types of parsers

1. Arithmetic string -> Reverse polish with tokens  :  string -> vector<Tokens>
2. Reverse polish -> applying all operations

*/

// Todo: make everything on shared_ptr
class Token
{
  public:
    enum Token_types
    {
        Const_integer,
        Const_string,
        Const_byte,
        Const_bool,
        Variable,
        Par_left,
        Par_right,
        Op_not,
        Op_mul,
        Op_div,
        Op_mod,
        Op_plus,
        Op_minus,
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

    Token(int &pos, const std::string &origin_str)
    {
        if (origin_str[pos] == '0')
        {
            if (origin_str[pos + 1] == 'x')
            {
                type = Token_types::Const_byte;
                pos += 2;
                int start = pos;
                int count = 0;
                while (std::isdigit((static_cast<unsigned char>(origin_str[pos]))) ||
                       (origin_str[pos] >= 'a' && origin_str[pos] <= 'f'))
                {
                    count++;
                    pos++;
                }
                value = origin_str.substr(start, count);
            }
            else
            {
                type = Token_types::Const_integer;
                int start = pos;
                int count = 0;
                while (std::isdigit((static_cast<unsigned char>(origin_str[pos]))))
                {
                    count++;
                    pos++;
                }
                value = origin_str.substr(start, count);
            }
        }
        else if (origin_str[pos] == '\"')
        {
            type = Token_types::Const_string;
            pos++;
            value.reserve(32);
            while (origin_str[pos] != '\"' && origin_str[pos] != '\0')
            {
                // TODO: Add freaking numeric esacpe seq
                if (origin_str[pos] == '\\')
                {
                    pos++;
                    switch (origin_str[pos])
                    {
                    case '\'':
                        value.push_back('\'');
                        break;
                    case '\"':
                        value.push_back('\"');
                        break;
                    case '\?':
                        value.push_back('\?');
                        break;
                    case '\\':
                        value.push_back('\\');
                        break;
                    case '\a':
                        value.push_back('\a');
                        break;
                    case '\b':
                        value.push_back('\b');
                        break;
                    case '\f':
                        value.push_back('\f');
                        break;
                    case '\n':
                        value.push_back('\n');
                        break;
                    case '\r':
                        value.push_back('\r');
                        break;
                    case '\t':
                        value.push_back('\t');
                        break;
                    case '\v':
                        value.push_back('\v');
                        break;
                    default:
                        throw std::runtime_error("Unsupported or wrong escape sequence found ");
                        break;
                    }
                }
                else
                {
                    value.push_back(origin_str[pos]);
                }
                pos++;
            }
            if (origin_str[pos] != '\0')
            {
                throw std::runtime_error("Unclosed \" was found");
            }
        }
        else if (std::isdigit((static_cast<unsigned char>(origin_str[pos]))))
        {
            type = Token_types::Const_integer;
            int start = pos;
            int count = 0;
            while (std::isdigit((static_cast<unsigned char>(origin_str[pos]))))
            {
                count++;
                pos++;
            }
            value = origin_str.substr(start, count);
        }
        else if (std::isalpha((static_cast<unsigned char>(origin_str[pos]))))
        {
            type = Token_types::Variable;
            int start = pos;
            int count = 0;
            while (std::isalpha((static_cast<unsigned char>(origin_str[pos]))) ||
                   std::isdigit((static_cast<unsigned char>(origin_str[pos]))) || origin_str[pos] == '_' ||
                   origin_str[pos] == '.')
            {
                count++;
                pos++;
            }
            value = origin_str.substr(start, count);
        }
        else if (origin_str[pos] == '!')
        {
            pos++;
            if (origin_str[pos] == '=')
            {
                type = Token_types::Op_noteq;
            }
            else
            {
                type = Token_types::Op_not;
            }
            pos++;
        }
        else if (origin_str[pos] == '*')
        {
            type = Token_types::Op_not;
            pos++;
        }
        else if (origin_str[pos] == '\\')
        {
            type = Token_types::Op_div;
            pos++;
        }
        else if (origin_str[pos] == '%')
        {
            type = Token_types::Op_mod;
            pos++;
        }
        else if (origin_str[pos] == '+')
        {
            type = Token_types::Op_plus;
            pos++;
        }
        else if (origin_str[pos] == '-')
        {
            type = Token_types::Op_minus;
            pos++;
        }
        else if (origin_str[pos] == '>')
        {
            pos++;
            if (origin_str[pos] == '=')
            {
                type = Token_types::Op_geq;
            }
            else
            {
                type = Token_types::Op_g;
            }
            pos++;
        }
        else if (origin_str[pos] == '<')
        {
            pos++;
            if (origin_str[pos] == '=')
            {
                type = Token_types::Op_leq;
            }
            else
            {
                type = Token_types::Op_l;
            }
            pos++;
        }
        else if (origin_str[pos] == '&' && origin_str[pos + 1] == '&')
        {
            type = Token_types::Op_and;
            pos += 2;
        }
        else if (origin_str[pos] == '^' && origin_str[pos + 1] == '^')
        {
            type = Token_types::Op_xor;
            pos += 2;
        }
        else if (origin_str[pos] == '|' && origin_str[pos + 1] == '|')
        {
            type = Token_types::Op_and;
            pos += 2;
        }
        else if (origin_str[pos] == '(')
        {
            type = Token_types::Par_left;
            pos++;
        }
        else if (origin_str[pos] == ')')
        {
            type = Token_types::Par_right;
            pos++;
        }
        else
        {
            throw std::runtime_error("Unknown token was found ");
        }
    }

    Token_types get_type() const
    {
        return type;
    }

    bool is_operation() const
    {
        return type >= Token::Token_types::Op_not; // See Token_types order for understanding this
    }

  private:
    Token_types type;
    std::string value;
}; // class Token

class ArithmParser
{

  public:
    ArithmParser() = delete;
    std::vector<std::shared_ptr<Token>> arithm_parse(std::string origin_str)
    {
        origin_str.push_back('\0');
        std::vector<std::shared_ptr<Token>> output;
        std::vector<std::shared_ptr<Token>> op_stack;
        std::vector<std::shared_ptr<Token>> input;

        int cur_pos = 0;
        while (cur_pos != origin_str.length())
        {
            while (std::isspace(static_cast<unsigned char>(origin_str[cur_pos])))
            {
                if (origin_str[cur_pos] == '\n')
                    break;
                cur_pos++;
            }
            if (origin_str[cur_pos] == '\n')
                break;
            input.emplace_back(std::make_shared<Token>(cur_pos, origin_str));
        }
        reverse(input.begin(), input.end());

        // https://en.wikipedia.org/wiki/Shunting_yard_algorithm
        for (std::shared_ptr<Token> &cur_token : input)
        {
            if (cur_token->is_operation())
            {
                while (!op_stack.empty() && operations_precedence[cur_token->get_type()] >=
                                                operations_precedence[op_stack.back()->get_type()])
                {
                    output.emplace_back(op_stack.back());
                    op_stack.pop_back();
                }
                op_stack.emplace_back(cur_token);
            }
            else if (cur_token->get_type() == Token::Token_types::Par_left)
            {
                op_stack.emplace_back(cur_token);
            }
            else if (cur_token->get_type() == Token::Token_types::Par_right)
            {
                while (!op_stack.empty() && op_stack.back()->get_type() != Token::Token_types::Par_left)
                {
                    output.emplace_back(op_stack.back());
                    op_stack.pop_back();
                }
            }
            else
            {
                op_stack.emplace_back(cur_token);
            }
        }
        return output;
    }

  private:
    std::map<Token::Token_types, int> operations_precedence = {
        {Token::Token_types::Op_not, 0}, {Token::Token_types::Op_mul, 1},   {Token::Token_types::Op_div, 1},
        {Token::Token_types::Op_mod, 1}, {Token::Token_types::Op_plus, 2},  {Token::Token_types::Op_minus, 2},
        {Token::Token_types::Op_eq, 3},  {Token::Token_types::Op_noteq, 3}, {Token::Token_types::Op_l, 3},
        {Token::Token_types::Op_leq, 3}, {Token::Token_types::Op_g, 3},     {Token::Token_types::Op_geq, 3},
        {Token::Token_types::Op_and, 4}, {Token::Token_types::Op_xor, 5},   {Token::Token_types::Op_or, 6}};
};