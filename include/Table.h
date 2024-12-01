#pragma once

#include <iostream>
#include <list>
#include <map>
#include <string>
#include <vector>

#include "ColumnInfo.h"
#include "Condition.h"
#include "Row.h"

class TableIterator
{
  public:
    TableIterator(std::list<Row>::iterator it) : it(it)
    {
    }
    TableIterator &operator++()
    {
        it++;
        return *this;
    }
    TableIterator operator++(int)
    {
        TableIterator tmp = *this;
        ++(*this);
        return tmp;
    }
    TableIterator &operator--()
    {
        it--;
        return *this;
    }
    TableIterator operator--(int)
    {
        TableIterator tmp = *this;
        --(*this);
        return tmp;
    }
    bool operator==(const TableIterator &rhs) const
    {
        return it == rhs.it;
    }
    bool operator!=(const TableIterator &rhs) const
    {
        return it != rhs.it;
    }
    const Row &operator*() const
    {
        return *it;
    }

  private:
    std::list<Row>::iterator it;
};

class Table
{
  public:
    Table() = default;
    Table(bool s, std::string msg = "") : status(s), columns(), columnOrder(), rows(), errorMsg(msg)
    {
    }

    Table &operator=(const Table &other) = delete;
    Table(const Table &other) = delete;

    Table &operator=(Table &&other)
    {
        if (this != &other)
        {
            columns = other.columns;
            columnOrder = other.columnOrder;
            name = other.name;
            status = other.status;
            errorMsg = other.errorMsg;

            rows.clear();
            for (auto &it : other.rows)
            {
                rows.emplace_back(std::move(it));
                rows.back().columns = &columns;
            }
        }
        return *this;
    }

    Table(Table &&other)
        : columns(other.columns), columnOrder(other.columnOrder), name(other.name), status(other.status),
          errorMsg(other.errorMsg)
    {
        rows.clear();
        for (auto &it : other.rows)
        {
            rows.emplace_back(std::move(it));
            rows.back().columns = &columns;
        }
    }

    bool is_ok()
    {
        return status;
    }

    std::string what()
    {
        return errorMsg;
    }

    std::vector<std::string> getColumns()
    {
        std::vector<std::string> ret;
        for (auto &it : columnOrder)
        {
            ret.push_back(it.second);
        }
        return ret;
    }

    Table insertArr(std::vector<std::optional<std::string>> row);
    Table insertMap(std::map<std::string, std::string> row);
    Table select(std::vector<std::string> columns, std::string cond);
    Table deleteRows(std::string cond);
    Table update(std::string allexpr, std::string cond);
    Table join(Table &other, std::string cond);
    Table createIndex(std::string col);
    void save(std::string path);
    void load(std::string path);

    TableIterator begin()
    {
        return TableIterator(rows.begin());
    }

    TableIterator end()
    {
        return TableIterator(rows.end());
    }

  private:
    std::map<std::string, ColumnInfo> columns;
    std::map<int, std::string> columnOrder;
    std::list<Row> rows;

    std::string name;

    bool status;
    std::string errorMsg;

    const char separator = '\t';

    friend class DataBase;
};