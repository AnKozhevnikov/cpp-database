%option nounistd
%option noyywrap
%option c++
%option case-insensitive
%option never-interactive

%{

    #include <iostream>
    #include <vector>
    #include "Funcparser.h"
    extern vector<FuncToken> mbuffer;
%}

string  \"[^\n"]+\"

spec_sym [{}=()\0,\[\]:]
word      [^{}(), \[\]:]+
sp [\t \n]

%%

{sp}    
{word} | {spec_sym} | {string}  {mbuffer.emplace(YYText());}



%%


#include "DataBase.h"
#include "FlexLexer.h"
#include "FuncParser.h"
#include "Table.h"
#include <algorithm>
#include <fstream>
#include <memory>
#include <string>

mParser::mParser() : yyFlexLexer() {};

void mParser::parse(std::string input)
{
    mbuffer.clear();
    istringstream tmp(input + string("\0"));

    FlexLexer::yylex(tmp, cout);
}

// Todo:: implement exepctions
Table DataBase::execute(string input)
{
    lex_parser.parse(input);
    switch (mbuffer[0].type)
    {
    case FT::create: {
        low_str(mbuffer[1].val);
        if (mbuffer[1].val != "table" || mbuffer[3].type != FT::open_par)
        {
            return Table(false);
        }

        FinetStateM mashine(mbuffer);
        string name = mbuffer[2].val;
        std::vector<std::tuple<std::string, std::shared_ptr<ValueType>, std::optional<std::string>, int>> columns;

        while (mbuffer[mashine.pos].type != FT::close_par && mbuffer[mashine.pos].type != FT::mend)
        {
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
        Table cur_table = get_table(pos);
        if (mbuffer[pos].type != FT::mset)
        {
            throw std::runtime_error("No set found in update");
        }
        pos++;
        string expr;
        for (; mbuffer[pos].type != FT::where && mbuffer[pos].type != FT::mend; pos++)
        {
            expr += mbuffer[pos].val;
        }
        if (mbuffer[pos].type == FT::mend)
        {
            throw std::runtime_error("No where found in update");
        }
        string cond;
        for (; mbuffer[pos].type != FT::mend; pos++)
        {
            cond += mbuffer[pos].val;
        }
        return cur_table.update(expr, cond);

        break;
    }
    case FT::mdelete: {
        string cur_table = mbuffer[1].val;
        int pos = 3;
        string cond;
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
        vector<string> col;
        for (; mbuffer[pos].type != FT::from && mbuffer[pos].type != FT::mend; pos++)
        {
            col.emplace_back(mbuffer[pos].val);
            if (mbuffer[pos].val == "*")
            {
                get_all = 1;
            }
        }
        pos++;
        Table cur_table = get_table(pos);
        if (get_all)
        {
            col = cur_table.getColumns();
        }
        pos++;
        string cond;
        for (; mbuffer[pos].type != FT::mend; pos++)
        {
            cond += mbuffer[pos].val;
        }
        return cur_table.select(col, cond);
        break;
    }
    default:
        break;
    }
}

std::tuple<std::string, std::shared_ptr<ValueType>, std::optional<std::string>, int> FinetStateM::next_col()
{
    int attr = pars_atr();
    if (mbuffer[pos].type != FT::other)
    {
        throw std::runtime_error("No col name");
    }
    string col_name = mbuffer[pos].val;
    pos++;
    if (mbuffer[pos].type != FT::separator)
    {
        throw std::runtime_error("No : found for column");
    }
    pos++;
    std::shared_ptr<ValueType> column_type = pars_type();
    optional<string> default_val = nullopt;
    if (mbuffer[pos].type == FT::eq)
    {
        pos++;
        if (mbuffer[pos].type != FT::other)
        {
            throw std::runtime_error("Strange default value for column");
        }
        default_val = mbuffer[pos].val;
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
Table DataBase::get_table(int &start)
{
    if (mbuffer[start].type != FT::other)
    {
        throw std::runtime_error("No name for left table in join");
    }
    if (mbuffer[start + 1].type != FT::join)
    {
        if (tables.find(mbuffer[start + 1].val) == tables.end())
        {
            throw std::runtime_error("Table with given name doesnt exists");
        }
        else
        {
            start++;
            return tables[mbuffer[start - 1].val];
        }
    }
    else
    {
        string s1 = mbuffer[start].val;
        string s2 = mbuffer[start + 2].val;
        string cond;
        start += 3;
        if (mbuffer[start].type != FT::on)
        {
            return join(s1, s2, cond);
        }
        else
        {
            start++;
            for (; mbuffer[start].type == FT::other; start++)
            {
                cond += mbuffer[start].val;
            }
            return join(s1, s2, cond);
        }
    }
}

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
        return make_shared<ValueType>(Types::String);
    }
    else if (mbuffer[pos].val == "int32")
    {
        pos += 1;
        return make_shared<ValueType>(Types::Int);
    }
    else if (mbuffer[pos].val == "bytes")
    {
        if (mbuffer[pos + 1].type != FT::open_sqr || mbuffer[pos + 2].type != FT::other ||
            mbuffer[pos + 3].type != FT::close_sqr)
            throw std::runtime_error("No sqr brace for bool");
        int sz = stoi(mbuffer[pos + 2].val);
        pos += 4;
        return make_shared<ByteArrayType>(sz);
    }
    else if (mbuffer[pos].val == "bool")
    {
        pos += 1;
        return make_shared<ValueType>(Types::Bool);
    }
    else
    {
        throw std::runtime_error("Unknown type was found");
    }
}

static void low_str(string &str)
{
    transform(str.begin(), str.end(), str.begin(), [](unsigned char c) { return std::tolower(c); });
}
