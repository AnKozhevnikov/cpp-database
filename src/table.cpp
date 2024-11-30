#include <fstream>
#include <iostream>
#include <sstream>
#include <string>

#include "Creator.h"
#include "DataBase.h"
#include "Expression.h"
#include "Table.h"

Table Table::insertArr(std::vector<std::optional<std::string>> row)
{
    Row nRow(&columns);
    nRow.sz = row.size();

    if (nRow.sz != columns.size())
    {
        Table tab(false);
        return tab;
    }

    nRow.v.resize(nRow.sz);
    for (int i = 0; i < row.size(); ++i)
    {
        std::shared_ptr<ValueType> vt = columns[columnOrder[i]].vtype;
        std::unique_ptr<Cell> nCell;
        if (row[i] == std::nullopt)
        {
            if ((columns[columnOrder[i]].attr & AUTOINCREMENT) != 0 && rows.size() > 0)
            {
                nCell = rows.back().v[i]->clone();
                nCell->inc();
            }
            else if (columns[columnOrder[i]].baseValue.has_value())
            {
                nCell = Creator::generateCell(vt, columns[columnOrder[i]].baseValue.value());
            }
            else
            {
                Table tab(false);
                return tab;
            }
        }
        else
        {
            nCell = Creator::generateCell(vt, Creator::generateValue(vt, row[i].value()));
        }
        nRow.v[i] = std::move(nCell);
    }

    rows.emplace_back(std::move(nRow));

    Table tab(true);
    return std::move(tab);
}

Table Table::insertMap(std::map<std::string, std::string> row)
{
    Row nRow(&columns);
    nRow.sz = columns.size();
    nRow.v.resize(nRow.sz);
    for (auto it : columns)
    {
        std::string columnName = it.first;
        int num = it.second.number;
        std::shared_ptr<ValueType> vt = it.second.vtype;
        Creator creator;
        std::unique_ptr<Cell> nCell = nullptr;
        if (row.find(columnName) == row.end())
        {
            if ((it.second.attr & AUTOINCREMENT) != 0 && rows.size() > 0)
            {
                nCell = rows.back().v[num]->clone();
                nCell->inc();
            }
            else if (it.second.baseValue.has_value())
            {
                nCell = creator.generateCell(vt, it.second.baseValue.value());
            }
            else
            {
                Table tab(false);
                return tab;
            }
        }
        else
        {
            nCell = creator.generateCell(vt, creator.generateValue(vt, row[columnName]));
        }

        nRow.v[num] = std::move(nCell);
    }

    rows.emplace_back(std::move(nRow));

    Table tab(true);
    return std::move(tab);
}

void Table::save(std::string path)
{
    std::string tpath = path + "/" + name + ".tsv";
    std::string ipath = path + "/" + name + ".info";

    std::ofstream tstream(tpath);
    for (auto &it1 : rows)
    {
        for (int i = 0; i < it1.v.size(); i++)
        {
            tstream << it1.v[i]->toString();
            if (i != it1.v.size() - 1)
            {
                tstream << separator;
            }
        }
        tstream << "\n";
    }
    tstream.close();

    std::ofstream istream(ipath);
    for (auto it2 : columns)
    {
        istream << it2.first << separator << Creator::stringFromValueType(it2.second.vtype) << separator
                << it2.second.attr << separator << it2.second.number;
        if (it2.second.baseValue.has_value())
        {
            std::unique_ptr<Cell> nCell = Creator().generateCell(it2.second.vtype, it2.second.baseValue.value());
            istream << separator << nCell->toString();
        }
        istream << std::endl;
    }
    istream.close();
}

void Table::load(std::string path)
{
    std::string tpath = path + "/" + name + ".tsv";
    std::string ipath = path + "/" + name + ".info";

    std::ifstream istream(ipath);
    std::string line;
    while (std::getline(istream, line))
    {
        std::stringstream ss(line);
        std::string buf;
        std::string columnName;

        std::getline(ss, columnName, separator);

        std::getline(ss, buf, separator);
        std::shared_ptr<ValueType> vtype = Creator().generateValueType(buf);

        std::getline(ss, buf, separator);
        int attr = std::stoi(buf);

        std::getline(ss, buf, separator);
        int number = std::stoi(buf);

        std::optional<std::any> baseValue = std::nullopt;
        if (std::getline(ss, buf, separator))
        {
            baseValue = Creator().generateValue(vtype, buf);
        }
        columns[columnName].vtype = vtype;
        columns[columnName].attr = attr;
        columns[columnName].number = number;
        columns[columnName].baseValue = baseValue;

        columnOrder[number] = columnName;
    }
    istream.close();

    std::ifstream tstream(tpath);
    while (std::getline(tstream, line))
    {
        std::stringstream ss(line);
        Row nRow(&columns);
        nRow.sz = columns.size();
        nRow.v.resize(nRow.sz);
        for (int i = 0; i < nRow.sz; i++)
        {
            std::string cell;
            std::getline(ss, cell, separator);
            Creator creator;
            nRow.v[i] = creator.generateCell(columns[columnOrder[i]].vtype,
                                             creator.generateValue(columns[columnOrder[i]].vtype, cell));
        }
        rows.emplace_back(std::move(nRow));
    }
    tstream.close();
}

Table Table::select(std::vector<std::string> cols, std::string cond)
{
    Table res(false);
    for (auto it : cols)
    {
        if (this->columns.find(it) == this->columns.end())
        {
            return res;
        }
    }

    Table ret(true);
    ret.name = name;
    for (int i = 0; i < cols.size(); i++)
    {
        ret.columnOrder[i] = cols[i];
        ret.columns[cols[i]] = columns[cols[i]];
        ret.columns[cols[i]].number = i;
    }

    Condition condition(cond);
    for (auto &it : rows)
    {
        bool flag = condition.apply(it);
        if (!flag)
        {
            continue;
        }

        Row nRow(&ret.columns);
        nRow.sz = cols.size();
        nRow.v.resize(nRow.sz);
        for (int i = 0; i < cols.size(); i++)
        {
            nRow.v[i] = it.v[columns[cols[i]].number]->clone();
        }
        ret.rows.emplace_back(std::move(nRow));
    }

    return std::move(ret);
}

Table Table::deleteRows(std::string cond)
{
    Table ret(true);
    ret.name = name;
    ret.columns = columns;
    ret.columnOrder = columnOrder;

    Condition condition(cond);
    auto it = rows.begin();
    while (it != rows.end())
    {
        bool flag = condition.apply(*it);
        if (flag)
        {
            auto itSwap = it;
            ++itSwap;
            ret.rows.emplace_back(std::move(*it));
            rows.erase(it);
            it = itSwap;
        }
        else
        {
            ++it;
        }
    }

    return ret;
}

Table Table::update(std::string allexpr, std::string cond)
{
    ExpressionParcer expr(allexpr);
    Condition condition(cond);
    for (auto &it : rows)
    {
        bool flag = condition.apply(it);
        if (!flag)
        {
            continue;
        }

        std::vector<std::unique_ptr<Cell>> values = expr.get_values(it);
        for (int i = 0; i < values.size(); i++)
        {
            it.v[columns[expr.updating[i]].number] = std::move(values[i]);
        }
    }

    Table ret(true);
    return ret;
}

Table Table::join(Table &other, std::string cond)
{
    Table ret(false);
    if (other.columns.size() == 0)
    {
        return ret;
    }

    for (auto &it : columns)
    {
        ret.columns[it.first] = it.second;
        ret.columnOrder[it.second.number] = it.first;
    }

    for (auto &it : other.columns)
    {
        if (ret.columns.find(it.first) != ret.columns.end())
        {
            return ret;
        }
        ret.columns[it.first] = it.second;
        ret.columns[it.first].number = this->columns.size() + it.second.number;
        ret.columnOrder[this->columns.size() + it.second.number] = it.first;
    }

    Condition condition(cond);
    for (auto &it1 : rows)
    {
        for (auto &it2 : other.rows)
        {
            Row nRow(&ret.columns);
            nRow.sz = ret.columns.size();
            for (auto &it : it1.v)
            {
                nRow.v.push_back(it->clone());
            }
            for (auto &it : it2.v)
            {
                nRow.v.push_back(it->clone());
            }
            nRow.v.shrink_to_fit();
            if (condition.apply(nRow))
            {
                ret.rows.emplace_back(std::move(nRow));
            }
        }
    }

    ret.status = true;
    return ret;
}