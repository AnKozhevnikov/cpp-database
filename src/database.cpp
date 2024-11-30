#include <DataBase.h>
#include <filesystem>
#include <set>

Table DataBase::createTable(std::string s,
                                      std::vector<std::tuple<std::string, std::shared_ptr<ValueType>, std::optional<std::string>, int>> info)
{
    if (tables.find(s) != tables.end())
    {
        Table t(false);
        return t;
    }

    tables[s].status = true;
    tables[s].name = s;

    for (int i = 0; i < info.size(); ++i)
    {
        std::string columnName = std::get<std::string>(info[i]);
        tables[s].columns[columnName].number = i;
        tables[s].columns[columnName].attr = std::get<int>(info[i]);
        tables[s].columns[columnName].vtype = std::get<std::shared_ptr<ValueType>>(info[i]);
        if (std::get<std::optional<std::string>>(info[i]).has_value())
        {
            tables[s].columns[columnName].baseValue = Creator::generateValue(tables[s].columns[columnName].vtype, std::get<std::optional<std::string>>(info[i]).value());
        }
        else
        {
            tables[s].columns[columnName].baseValue = std::nullopt;
        }

        tables[s].columnOrder[i] = columnName;
    }

    Table t(true);
    return std::move(t);
}

Table DataBase::insertArr(std::string s, std::vector<std::optional<std::string>> row)
{
    if (tables.find(s) == tables.end() || tables[s].columns.size() != row.size())
    {
        Table t(false);
        return t;
    }

    return tables[s].insertArr(row);
}

Table DataBase::insertMap(std::string s, std::map<std::string, std::string> row)
{
    if (tables.find(s) == tables.end() || tables[s].columns.size() != row.size())
    {
        Table t(false);
        return t;
    }

    return tables[s].insertMap(row);
}

void DataBase::save(std::string path)
{
    std::error_code ec;
    bool res = std::filesystem::create_directory(path, ec);
    if (!res && ec)
    {
        throw std::runtime_error("Error creating directory");
    }

    for (auto &it : tables)
    {
        it.second.save(path);
    }
}

void DataBase::load(std::string path)
{
    std::set<std::string> tsvs;
    std::set<std::string> infos;

    for (const auto &dirEntry : std::filesystem::directory_iterator(path))
    {
        std::string f = dirEntry.path().string();
        std::string name = f.substr(f.find_last_of('/') + 1);
        if (name.find(".tsv") != std::string::npos)
        {
            tsvs.insert(name.substr(0, name.find(".tsv")));
        }
        else if (name.find(".info") != std::string::npos)
        {
            infos.insert(name.substr(0, name.find(".info")));
        }
    }

    for (const auto &it : tsvs)
    {
        if (infos.find(it) == infos.end())
        {
            throw std::runtime_error("No info file for table " + it);
        }
    }

    for (const auto &it : infos)
    {
        if (tsvs.find(it) == tsvs.end())
        {
            throw std::runtime_error("No tsv file for table " + it);
        }
        tables[it].status = true;
        tables[it].name = it;
        tables[it].load(path);
    }
}

Table DataBase::select(std::string s, std::vector<std::string> cols, std::string cond)
{
    if (tables.find(s) == tables.end())
    {
        Table t(false);
        return t;
    }

    Table ret = tables[s].select(cols, cond);

    return std::move(ret);
}

Table DataBase::deleteRows(std::string s, std::string cond)
{
    if (tables.find(s) == tables.end())
    {
        Table t(false);
        return t;
    }

    return tables[s].deleteRows(cond);
}

Table DataBase::update(std::string s, std::string allexpr, std::string cond)
{
    if (tables.find(s) == tables.end())
    {
        Table t(false);
        return t;
    }

    return tables[s].update(allexpr, cond);
}

Table DataBase::join(std::string s1, std::string s2, std::string cond)
{
    if (tables.find(s1) == tables.end() || tables.find(s2) == tables.end())
    {
        Table t(false);
        return t;
    }

    return tables[s1].join(tables[s2], cond);
}

Table DataBase::createIndex(std::string s, std::string col)
{
    if (tables.find(s) == tables.end())
    {
        Table t(false);
        return t;
    }

    return tables[s].createIndex(col);
}