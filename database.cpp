#include <DataBase.h>

DataBase::Table DataBase::createTable(std::string s,
                                      std::vector<std::tuple<std::string, Types, std::optional<std::any>, int>> info)
{
    

    Table t(true);
    t.name = s;

    for (int i = 0; i < info.size(); ++i)
    {
        std::string columnName = std::get<std::string>(info[i]);
        t.columns[columnName].number = i;
        t.columns[columnName].attr = std::get<int>(info[i]);
        t.columns[columnName].type = std::get<Types>(info[i]);
        t.columns[columnName].baseValue = std::get<std::optional<std::any>>(info[i]);
    }

    return t;
}

DataBase::Table DataBase::insert(std::string s, std::vector<std::optional<std::any>> row)
{
    if (tables.find(s) != tables.end() || tables[s].columns.size() != row.size())
    {
        tables.erase(s);
        Table t(false);
        return t;
    }

    return tables[s].insert(row);
}