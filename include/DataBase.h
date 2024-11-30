#pragma once

#include <any>
#include <list>
#include <map>
#include <memory>
#include <optional>
#include <stdexcept>
#include <string>
#include <vector>

#include "Cell.h"
#include "Condition.h"
#include "Table.h"
#include "Types.h"

#define UNIQUE 1
#define AUTOINCREMENT 2
#define KEY 4

class DataBase
{
  private:
    std::map<std::string, Table> tables;

  public:
    Table createTable(
        std::string s,
        std::vector<std::tuple<std::string, std::shared_ptr<ValueType>, std::optional<std::string>, int>> info);
    Table insertArr(std::string s, std::vector<std::optional<std::string>> row);
    Table insertMap(std::string s, std::map<std::string, std::string> row);
    Table select(std::string s, std::vector<std::string> cols, std::string cond);
    Table deleteRows(std::string s, std::string cond);
    Table update(std::string s, std::string allexpr, std::string cond);
    Table join(std::string s1, std::string s2, std::string cond);
    Table createIndex(std::string s, std::string col);

    Table execute(std::string q);
    void save(std::string path);
    void load(std::string path);
};