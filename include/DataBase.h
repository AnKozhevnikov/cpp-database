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
#include "Table.h"
#include "Types.h"

#define UNIQUE 1
#define AUTOINCREMENT 2
#define KEY 4

class DataBase
{
  private:
    Table createTable(std::string s, std::vector<std::tuple<std::string, std::shared_ptr<ValueType>, std::optional<std::any>, int>> info);
    Table insert(std::string s, std::vector<std::optional<std::any>> row);

    

  public:
    std::map<std::string, Table> tables;
    Table query(std::string q);
    void save(std::string path);
    void load(std::string path);
};