#include <DataBase.h>
#include <filesystem>

DataBase::Table DataBase::createTable(std::string s,
                                      std::vector<std::tuple<std::string, Types, std::optional<std::any>, int>> info)
{
    if (tables.find(s) != tables.end())
    {
        Table t(false);
        return t;
    }

    tables[s].name = s;

    for (int i = 0; i < info.size(); ++i)
    {
        std::string columnName = std::get<std::string>(info[i]);
        tables[s].columns[columnName].number = i;
        tables[s].columns[columnName].attr = std::get<int>(info[i]);
        tables[s].columns[columnName].type = std::get<Types>(info[i]);
        tables[s].columns[columnName].baseValue = std::get<std::optional<std::any>>(info[i]);
    }

    Table t(true);
    return t;
}

DataBase::Table DataBase::insert(std::string s, std::vector<std::optional<std::any>> row)
{
    if (tables.find(s) == tables.end() || tables[s].columns.size() != row.size())
    {
        Table t(false);
        return t;
    }

    return tables[s].insert(row);
}

DataBase::Table DataBase::query(std::string str) {
    //placeholder
    std::tuple<std::string, Types, std::optional<std::any>, int> t = {"inc", Int, 0, AUTOINCREMENT};
    std::vector<std::tuple<std::string, Types, std::optional<std::any>, int>> v = {t};
    createTable("amogus", v);

    insert("amogus", {std::nullopt});
    return insert("amogus", {std::nullopt});
}

void DataBase::save(std::string path)
{
    std::error_code ec;
    bool res = std::filesystem::create_directory(path, ec);
    if (!res && ec)
    {
        throw std::runtime_error("Error creating directory");
    }

    for (auto& it : tables)
    {
        it.second.save(path);
    }
}