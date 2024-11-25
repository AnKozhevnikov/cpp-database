#include <fstream>
#include <string>
#include <sstream>
#include <iostream>

#include "DataBase.h"
#include "Creator.h"
#include "Table.h"

Table Table::insert(std::vector<std::optional<std::any>> row)
{
    Row nRow(columns);
    nRow.sz = row.size();
    nRow.v.resize(nRow.sz);
    for (auto it : columns)
    {
        int num = it.second.number;
        std::shared_ptr<ValueType> vt = it.second.vtype;
        Creator creator;
        std::unique_ptr<Cell> nCell = nullptr;
        if (!row[num].has_value())
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
            nCell = creator.generateCell(vt, row[num].value());
        }

        

        nRow.v[num] = std::move(nCell);
    }

    rows.emplace_back(std::move(nRow));

    Table tab(true);
    return tab;
}

void Table::save(std::string path)
{
    std::string tpath = path + "/" + name + ".csv";
    std::string ipath = path + "/" + name + ".info";

    std::ofstream tstream(tpath);
    for (auto& it1 : rows)
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
        istream << it2.first << separator << Creator::stringFromValueType(it2.second.vtype) << separator << it2.second.attr << separator << it2.second.number;
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
    std::string tpath = path + "/" + name + ".csv";
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

        std::getline(ss, buf, separator);
        std::optional<std::any> baseValue = std::nullopt;
        if (buf != "")
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
        Row nRow(columns);
        nRow.sz = columns.size();
        nRow.v.resize(nRow.sz);
        for (int i = 0; i < nRow.sz; i++)
        {
            std::string cell;
            std::getline(ss, cell, separator);
            Creator creator;
            nRow.v[i] = creator.generateCell(columns[columnOrder[i]].vtype, creator.generateValue(columns[columnOrder[i]].vtype, cell).value());
        }
        rows.emplace_back(std::move(nRow));
    }
    tstream.close();
}