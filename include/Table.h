#pragma once

#include <map>
#include <string>
#include <list>
#include <vector>

#include "Row.h"
#include "ColumnInfo.h"

class Table
{
  public:
    Table() = default;
    Table(bool s) : status(s)
    {
    }

    bool is_ok()
    {
        return status;
    }

  private:
    std::map<std::string, ColumnInfo> columns;
    std::map<int, std::string> columnOrder;
    std::list<Row> rows;
    std::string name;

    bool status;

    Table insert(std::vector<std::optional<std::any>> row);

    void save(std::string path);
    void load(std::string path);

    friend class DataBase;
};