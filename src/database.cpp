#include <DataBase.h>
#include <filesystem>
#include <set>

Table DataBase::createTable(std::string s,
                                      std::vector<std::tuple<std::string, std::shared_ptr<ValueType>, std::optional<std::any>, int>> info)
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
        tables[s].columns[columnName].baseValue = std::get<std::optional<std::any>>(info[i]);

        tables[s].columnOrder[i] = columnName;
    }

    Table t(true);
    return std::move(t);
}

Table DataBase::insert(std::string s, std::vector<std::optional<std::any>> row)
{
    if (tables.find(s) == tables.end() || tables[s].columns.size() != row.size())
    {
        Table t(false);
        return t;
    }

    return tables[s].insert(row);
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

Table DataBase::select(std::string s, std::vector<std::string> cols, Condition &cond)
{
    if (tables.find(s) == tables.end())
    {
        Table t(false);
        return t;
    }

    Table ret = tables[s].select(cols, cond);

    return std::move(ret);
}

Table DataBase::deleteRows(std::string s, Condition &cond)
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

Table DataBase::query(std::string str)
{
    // placeholder
    std::tuple<std::string, std::shared_ptr<ValueType>, std::optional<std::any>, int> t1 = {"c1", std::make_shared<ValueType>(Int), 0, AUTOINCREMENT};
    std::tuple<std::string, std::shared_ptr<ValueType>, std::optional<std::any>, int> t2 = {"c2", std::make_shared<ValueType>(Int), 0, 0};
    std::tuple<std::string, std::shared_ptr<ValueType>, std::optional<std::any>, int> t3 = {"c3", std::make_shared<ValueType>(String), std::string("baseString"), 0};
    std::vector<std::tuple<std::string, std::shared_ptr<ValueType>, std::optional<std::any>, int>> v = {t1, t2, t3};
    createTable("amogus", v);

    insert("amogus", {std::nullopt, std::nullopt, std::nullopt});
    insert("amogus", {std::nullopt, std::nullopt, std::string("s1")});
    insert("amogus", {std::nullopt, 2, std::string("s2")}); 
    
    Condition cond("c1=c2");
    Table r = select("amogus", {"c3"}, cond);
    return r;

    /*Condition cond(str);
    return select("amogus", {"c2", "c1"}, cond);
    return deleteRows("amogus", cond);*/
}