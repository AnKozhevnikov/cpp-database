#include <DataBase.h>
#include <fstream>
#include <experimental/filesystem>

DataBase::Table DataBase::Table::insert(std::vector<std::optional<std::any>> row)
{
    Row nRow;
    nRow.sz = row.size();
    nRow.v.resize(nRow.sz);
    for (auto it : columns)
    {
        int num = it.second.number;
        Types t = it.second.type;
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
                nCell = creator.generateCell(t, it.second.baseValue.value());
            }
            else
            {
                Table tab(false);
                return tab;
            }
        }
        else
        {
            nCell = creator.generateCell(t, row[num].value());
        }

        nRow.v[num] = std::move(nCell);
    }

    rows.emplace_back(std::move(nRow));

    Table tab(true);
    return tab;
}

void DataBase::Table::save(std::string path)
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
                tstream << ",";
            }
        }
        tstream << "\n";
    }
    tstream.close();

    std::ofstream istream(ipath);
    for (auto it2 : columns)
    {
        istream << it2.first << "," << it2.second.type << "," << it2.second.attr << it2.second.number;
        if (it2.second.baseValue.has_value())
        {
            std::unique_ptr<Cell> nCell = Creator().generateCell(it2.second.type, it2.second.baseValue.value());
            istream << "," << nCell->toString();
        }
        istream << std::endl;
    }
    istream.close();
}