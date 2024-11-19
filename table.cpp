#include <DataBase.h>

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
        if (row[num].has_value())
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

    Table tab(true);
    return tab;
}