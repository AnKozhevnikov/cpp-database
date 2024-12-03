%option nounistd
%option noyywrap
%option c++
%option case-insensitive
%option never-interactive

%{

    #include <iostream>
    #include <vector>
    #include "FuncParser.h"
    std::vector<FuncToken> mbuffer;
%}

string  \"[^\n"]+\"

spec_sym [{}=()\0,\[\]:]
word      [^{}(), \[\]:]+
sp [\t \n]

%%

{sp}    
{word}  mbuffer.emplace_back(yytext);
{spec_sym} mbuffer.emplace_back(yytext);
{string}  mbuffer.emplace_back(yytext);



%%


#include "DataBase.h"
#include "FuncParser.h"
#include "Table.h"
#include <algorithm>
#include <sstream>
#include <memory>
#include <string>
#include <tuple>
mParser::mParser() : yyFlexLexer() {};
static void low_str(std::string &str)
{
    std::transform(str.begin(), str.end(), str.begin(), [](unsigned char c) { return std::tolower(c); });
}

void mParser::parse(std::string input)
{
    mbuffer.clear();
    std::istringstream tmp(input + std::string("\0"));

    FlexLexer::yylex(tmp, std::cout);
}
static std::tuple<int, std::string, std::string, std::string> get_table(int &start)
{
    if (mbuffer[start].type != FT::other)
    {
        throw std::runtime_error("No name for left table in join");
    }
    if (mbuffer[start + 1].type != FT::join)
    {

            start++;
            return make_tuple(0, mbuffer[start - 1].val, std::string(""), std::string(""));

    }
    else
    {
        std::string s1 = mbuffer[start].val;
        std::string s2 = mbuffer[start + 2].val;
        std::string cond;
        start += 3;
        if (mbuffer[start].type != FT::on)
        {
            return make_tuple(1, s1, s2, std::string(""));
        }
        else
        {
            start++;
            for (; mbuffer[start].type == FT::other; start++)
            {
                cond += mbuffer[start].val;
            }
            return make_tuple(1, s1, s2, cond);
        }
    }
}
// Todo:: implement exepctions
Table DataBase::execute(std::string input)
{
    lex_parser.parse(input);
    std::cout << mbuffer.size() <<std::endl;
    switch (mbuffer[0].type)
    {
    case FT::create: {
        low_str(mbuffer[1].val);
        if (mbuffer[1].val != "table" || mbuffer[3].type != FT::open_par)
        {
            return Table(false);
        }

        FinetStateM mashine(mbuffer);
        std::string name = mbuffer[2].val;
        std::vector<std::tuple<std::string, std::shared_ptr<ValueType>, std::optional<std::string>, int>> columns;

        while (mbuffer[mashine.pos].type != FT::close_par && mbuffer[mashine.pos].type != FT::mend)
        {
			if (mbuffer[mashine.pos].type == FT::mnext)
			{
				mashine.pos++;
			}
            try
            {
                columns.emplace_back(mashine.next_col());
            }
            catch (std::exception &e)
            {
                Table t(false, e.what());
                return t;
            }
        }
        return DataBase::createTable(name, columns);

        break;
    }
    case FT::update: {
        int pos = 1;
        auto cur_table = get_table(pos);
        if (mbuffer[pos].type != FT::mset)
        {
            throw std::runtime_error("No set found in update");
        }
        pos++;
        std::string expr;
        for (; mbuffer[pos].type != FT::where && mbuffer[pos].type != FT::mend; pos++)
        {
            expr += mbuffer[pos].val;
        }
        if (mbuffer[pos].type == FT::mend)
        {
            throw std::runtime_error("No where found in update");
        }
        std::string cond;
        for (; mbuffer[pos].type != FT::mend; pos++)
        {
            cond += mbuffer[pos].val;
        }
        if (std::get<0>(cur_table) == 0)
        {
            return update(std::get<1>(cur_table), expr, cond);
        }
        else
        {
            return join(std::get<1>(cur_table), std::get<2>(cur_table), std::get<3>(cur_table)).update(expr, cond);
        }
        

        break;
    }
    case FT::mdelete: {
        std::string cur_table = mbuffer[1].val;
        int pos = 3;
        std::string cond;
        for (; mbuffer[pos].type != FT::mend; pos++)
        {
            cond += mbuffer[pos].val;
        }
        return deleteRows(cur_table, cond);
        break;
    }
    case FT::mindex:
        /* code */
        break;
    case FT::mselect: {
        int pos = 1;
        int get_all = 0;
        std::vector<std::string> col;
        for (; mbuffer[pos].type != FT::from && mbuffer[pos].type != FT::mend; pos++)
        {
			if (mbuffer[pos].type == FT::mnext)
			{
				pos++;
			}
            col.emplace_back(mbuffer[pos].val);
            if (mbuffer[pos].val == "*")
            {
                get_all = 1;
            }
        }
        pos++;
        auto response = get_table(pos);
        
        pos++;
        std::string cond;
        for (; mbuffer[pos].type != FT::mend; pos++)
        {
            cond += mbuffer[pos].val;
        }
        if (std::get<0>(response) == 0)
        {
            if (get_all)
            {
                return select(std::get<1>(response), getColumnOfTable(std::get<1>(response)), cond);
            }
            else
            {
                return select(std::get<1>(response), col, cond);
            }
            
        }
        else
        {
            Table j_table = join(std::get<1>(response), std::get<2>(response), std::get<3>(response));
            if (get_all)
            {
                return j_table.select(j_table.getColumns() , cond);
            }
            else
            {
                return j_table.select(col , cond);;
            }
            
            
        }
        break;
    }
    default:
        return Table(false);
        break;
    }
}

std::tuple<std::string, std::shared_ptr<ValueType>, std::optional<std::string>, int> FinetStateM::next_col()
{
	std::cout << pos << std::endl;
    int attr = pars_atr();
    if (mbuffer[pos].type != FT::other)
    {
        throw std::runtime_error("No col name");
    }
    std::string col_name = mbuffer[pos].val;
    pos++;
    if (mbuffer[pos].type != FT::separator)
    {
        throw std::runtime_error("No : found for column");
    }
    pos++;
    std::shared_ptr<ValueType> column_type = pars_type();
    std::optional<std::string> default_val = std::nullopt;
    if (mbuffer[pos].type == FT::eq)
    {
        pos++;
        if (mbuffer[pos].type != FT::other)
        {
            throw std::runtime_error("Strange default value for column");
        }
        default_val = mbuffer[pos].val;
		pos++;
    }
    return make_tuple(col_name, column_type, default_val, attr);
}

int FinetStateM::pars_atr()
{
    int ans = 0;
    if (mbuffer[pos].type != FT::open_brace)
    {
        return ans;
    }
    for (; mbuffer[pos].type != FT::close_brace && mbuffer[pos].type != FT::mend; pos++)
    {
        low_str(mbuffer[pos].val);
        if (mbuffer[pos].val == "key")
        {
            ans |= KEY;
        }
        else if (mbuffer[pos].val == "unique")
        {
            ans |= UNIQUE;
        }
        else if (mbuffer[pos].val == "autoincrement")
        {
            ans |= AUTOINCREMENT;
        }
        else
        {
            throw std::runtime_error("No unknown atr was found");
        }
    }
    if (mbuffer[pos].type == FT::mend)
    {
        throw std::runtime_error("No close_brace");
    }
    pos++;
    return ans;
}

// Todo: implement rec search, exepctions


std::shared_ptr<ValueType> FinetStateM::pars_type()
{
    if (mbuffer[pos].type != FT::other)
    {
        throw std::runtime_error("No close_brace");
    }
    low_str(mbuffer[pos].val);
    if (mbuffer[pos].val == "string")
    {
        if (mbuffer[pos + 1].type != FT::open_sqr || mbuffer[pos + 2].type != FT::other ||
            mbuffer[pos + 3].type != FT::close_sqr)
            throw std::runtime_error("No sqr brace for string");
        pos += 4;
        return std::make_shared<ValueType>(Types::String);
    }
    else if (mbuffer[pos].val == "int32")
    {
        pos += 1;
        return std::make_shared<ValueType>(Types::Int);
    }
    else if (mbuffer[pos].val == "bytes")
    {
        if (mbuffer[pos + 1].type != FT::open_sqr || mbuffer[pos + 2].type != FT::other ||
            mbuffer[pos + 3].type != FT::close_sqr)
            throw std::runtime_error("No sqr brace for bool");
        int sz = stoi(mbuffer[pos + 2].val);
        pos += 4;
        return std::make_shared<ByteArrayType>(sz);
    }
    else if (mbuffer[pos].val == "bool")
    {
        pos += 1;
        return std::make_shared<ValueType>(Types::Bool);
    }
    else
    {
        throw std::runtime_error("Unknown type was found");
    }
}


