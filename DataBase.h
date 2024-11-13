#pragma once

#include <any>
#include <map>
#include <memory>
#include <optional>
#include <string>
#include <vector>

class DataBase
{
  public:
    auto query(std::string q);
  private:
    class Response
    {
        // TODO: implement
    };

    class Condition
    {
        // TODO: implement
    };

    class Expression
    {
        // TODO: implement
    };

    enum Types
    {
        Int,
        Bool,
        String,
        ByteArray
    };
    class Cell
    {
      public:
        virtual Cell opPlus(const Cell &right) const;
        virtual Cell opMinus(const Cell &right) const;
        virtual Cell opMult(const Cell &right) const;
        virtual Cell opDiv(const Cell &right) const;
        virtual Cell opMod(const Cell &right) const;
        virtual bool opG(const Cell &right) const;
        virtual bool opL(const Cell &right) const;
        virtual bool opEq(const Cell &right) const;
        virtual bool opGeq(const Cell &right) const;
        virtual bool opLeq(const Cell &right) const;
        virtual bool opNeq(const Cell &right) const;
        virtual Cell opAnd(const Cell &right) const;
        virtual Cell opOr(const Cell &right) const;
        virtual Cell opNot(const Cell &right) const;
        virtual Cell opXor(const Cell &right) const;
        virtual Cell opAbs(const Cell &right) const;
    };

    class IntCell : public Cell
    {
      public:
        /* Provide necessary methods*/
        int value;
    };

    class BoolCell : public Cell
    {
      public:
        /* Provide necessary methods*/
        bool value;
    };

    class StringCell : public Cell
    {
      public:
        /* Provide necessary methods*/
        std::string value;
    };

    class ByteArrayCell : public Cell
    {
      public:
        /* Provide necessary methods*/
        unsigned int sz;
        std::vector<int8_t> value;
    };

    class ColumnInfo
    {
      public:
        Types type;
        const int number;
        const std::any baseValue;
    };

    class Row
    {
      public:
        const int sz;
        std::vector<std::unique_ptr<Cell>> v;
    };

    class Table
    {
      public:
        Table() = default;

      private:
        std::map<std::string, ColumnInfo> columns;
        std::vector<Row> db;
        std::string name;

        Response createTable(std::vector<std::tuple<std::string, std::optional<std::any>, int>> info);
        Response insert(std::vector<std::unique_ptr<Cell>> row);
        Table select(std::vector<std::string> cols, Condition cond);
        Response update(Condition cond, std::vector<std::pair<std::string, Expression>> v);
        Response del(Condition cond);
    };

    Response createTable(std::string s, std::vector<std::tuple<std::string, std::optional<std::any>, int>> info);
    Response insert(std::string s, std::vector<std::unique_ptr<Cell>> row);
    Table select(std::string s, std::vector<std::string> cols, Condition cond);
    Response update(std::string s, Condition cond, std::vector<std::pair<std::string, Expression>> v);
    Response del(std::string s, Condition cond);
    Table join(std::string t1, std::string t2, Condition cond);
};