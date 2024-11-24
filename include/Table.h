#pragma once

#include <list>
#include <map>
#include <string>
#include <vector>

#include "ColumnInfo.h"
#include "Row.h"

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

    Table insert(std::vector<std::optional<std::any>> row);
    void save(std::string path);
    void load(std::string path);

  private:
    std::map<std::string, ColumnInfo> columns;
    std::map<int, std::string> columnOrder;
    std::list<Row> rows;
    std::string name;

    bool status;

    friend class DataBase;
};