#include <DataBase.h>
#include <algorithm>

static std::string strip(std::string str)
{
    int left = 0;
    int right = str.size() - 1;
    while (std::isspace(static_cast<unsigned char>(str[left])) && left < str.size())
        left++;
    if (left == str.size())
        return std::string("");
    while (std::isspace(static_cast<unsigned char>(str[right])))
        right--;
    return str.substr(left, right - left + 1);
}
static std::string get_space_word(std::string str, int &start)
{
    int left = start;
    bool is_opened = false;
    for (; start < str.size(); start++)
    {
        if (!std::isspace(static_cast<unsigned char>(str[start])) && !is_opened)
        {
            is_opened = true;
            left = start;
        }
        else if (std::isspace(static_cast<unsigned char>(str[start])) && is_opened)
        {

            return str.substr(left, start - left);
        }
    }
    return "";
}

static int unquote_find(std::string origin_str, std::string to_find, int start = 0)
{
    int first = 0;
    int second = origin_str.find(to_find);
    origin_str = origin_str.substr(start);
    for (; first != std::string::npos;
         first = origin_str.find(to_find, second + 1), second = origin_str.find(to_find, first + 1))
    {
        int pos = origin_str.find(to_find, first);
        if (pos == std::string::npos)
            return -1;
        if (pos < second)
        {
            return pos;
        }
        int moving_ptr = second;
        do
        {
            first = origin_str.find(to_find, moving_ptr + 1);
            moving_ptr = first;
        } while (first != std::string::npos && origin_str[first - 1] == '//');
        moving_ptr = first;

        do
        {
            second = origin_str.find(to_find, moving_ptr + 1);
            moving_ptr = first;
        } while (first != std::string::npos && origin_str[first - 1] == '//');
    }
    return -1;
}
Table DataBase::execute(std::string query)
{
    int pos = 0;
    std::string type_query = get_space_word(query, pos);
    std::transform(type_query.begin(), type_query.end(), type_query.begin(),
                   [](unsigned char c) { return std::tolower(c); });
    query = query.substr(pos);
    if (type_query == "create")
    {
        /*
        auto res = CreateQuery::parse(query.substr(pos));
        return createTable(res.first, res.second);
        */
    }
    else if (type_query == "insert")
    {
        int to_pos = query.find("to", query.rfind(')'));
        if (to_pos == -1)
            throw std::runtime_error("FuncParser:: no to in insert found");
        int prev = 0;
        std::vector<std::string> values;
        int next = unquote_find(query, std::string(","), prev);
            while (next != std::string::npos)
            {
                values.emplace_back(strip(query.substr(prev, next - prev)));
                prev = next + 1;
                next = unquote_find(query, std::string(","), prev);
            }
            values.emplace_back(strip(query.substr(prev, query.rfind(')') - prev)));
            
        if (unquote_find(query, std::string("="), prev) != -1)
        {
            std::map<std::string, std::string> map_values;
            for (std::string&  i : values)
            {
                int sep = unquote_find(i, std::string("="));
                map_values.insert({strip (i.substr(0, sep)), strip(i.substr(sep + 1))});
            }

        }
        else
        {
            std::vector<std::optional<std::string>> tmp(values.size());
            for (int i = 0; i < values.size(); i++)
            {
                if (values[i] == std::string(""))
                    tmp[i] = std::nullopt;
                else
                    tmp[i] = values[i];
            }
            return insertArr(strip(query.substr(to_pos + 2)), tmp);
        }

    }
    else if (type_query == "delete")
    {
        int where_pos = unquote_find(query, std::string("where"));
        std::string from_table;
        Condition tmp(std::string(""));
        if (where_pos == -1)
            return deleteRows(strip(query), tmp);
        from_table = strip(query.substr(0, where_pos));
        tmp = Condition(query.substr(where_pos + 5));
        return deleteRows(from_table, tmp);
    }
    else if (type_query == "update")
    {
        int set_pos = unquote_find(query, std::string("set"));
        int where_pos = unquote_find(query, std::string("where"));
        if (set_pos == -1)
            throw std::runtime_error("FuncParser:: no set in update found");
        if (where_pos == -1)
            return update(strip(query.substr(0, set_pos)), query.substr(set_pos + 3), "");
        return update(strip(query.substr(0, set_pos)), query.substr(set_pos + 3, where_pos - set_pos - 2),
                      query.substr(where_pos + 5));
    }
    else if (type_query == "select")
    {
        int from_pos = unquote_find(query, std::string("from"));
        int where_pos = unquote_find(query, std::string("where"));
        std::vector<std::string> columns;
        Condition tmp(std::string(""));
        if (from_pos == -1)
            throw std::runtime_error("FuncParser:: no from in select  found");
        int prev = 0;
        int next = unquote_find(query, std::string(","), prev);
        while (next != std::string::npos && next < from_pos)
        {
            columns.emplace_back(strip(query.substr(prev, next - prev)));
            prev = next + 1;
            next = unquote_find(query, std::string(","), prev);
        }
        columns.emplace_back(strip(query.substr(prev, where_pos - prev)));
        if (where_pos == -1)
        {
            return select(strip(query.substr(from_pos + 4, where_pos - from_pos - 4)), columns, tmp);
        }
        tmp = Condition(query.substr(where_pos + 5));
        return select(strip(query.substr(from_pos + 4, where_pos - from_pos - 4)), columns, tmp);
    }
    else
    {

        throw std::runtime_error("FuncParser:: No matching command was found");
    }
}
