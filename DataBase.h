#pragma once

#include <any>
#include <map>
#include <memory>
#include <optional>
#include <string>
#include <list>
#include <vector>

#define UNIQUE 1
#define AUTOINCREMENT 2
#define KEY 4

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
        virtual std::unique_ptr<Cell> opPlus(const std::unique_ptr<Cell> &right) const;
        virtual std::unique_ptr<Cell> opMinus(const std::unique_ptr<Cell> &right) const;
        virtual std::unique_ptr<Cell> opMult(const std::unique_ptr<Cell> &right) const;
        virtual std::unique_ptr<Cell> opDiv(const std::unique_ptr<Cell> &right) const;
        virtual std::unique_ptr<Cell> opMod(const std::unique_ptr<Cell> &right) const;
        virtual bool opG(const std::unique_ptr<Cell> &right) const;
        virtual bool opL(const std::unique_ptr<Cell> &right) const;
        virtual bool opEq(const std::unique_ptr<Cell> &right) const;
        virtual bool opGeq(const std::unique_ptr<Cell> &right) const;
        virtual bool opLeq(const std::unique_ptr<Cell> &right) const;
        virtual bool opNeq(const std::unique_ptr<Cell> &right) const;
        virtual std::unique_ptr<Cell> opAnd(const std::unique_ptr<Cell> &right) const;
        virtual std::unique_ptr<Cell> opOr(const std::unique_ptr<Cell> &right) const;
        virtual std::unique_ptr<Cell> opNot() const;
        virtual std::unique_ptr<Cell> opXor(const std::unique_ptr<Cell> &right) const;
        virtual int opAbs() const;
    };

    class IntCell : public Cell
    {
      public:
        IntCell(int v) : value(v) {}
        virtual std::unique_ptr<Cell> opPlus(const std::unique_ptr<Cell> &right) const;
        virtual std::unique_ptr<Cell> opMinus(const std::unique_ptr<Cell> &right) const;
        virtual std::unique_ptr<Cell> opMult(const std::unique_ptr<Cell> &right) const;
        virtual std::unique_ptr<Cell> opDiv(const std::unique_ptr<Cell> &right) const;
        virtual std::unique_ptr<Cell> opMod(const std::unique_ptr<Cell> &right) const;
        virtual bool opG(const std::unique_ptr<Cell> &right) const;
        virtual bool opL(const std::unique_ptr<Cell> &right) const;
        virtual bool opEq(const std::unique_ptr<Cell> &right) const;
        virtual bool opGeq(const std::unique_ptr<Cell> &right) const;
        virtual bool opLeq(const std::unique_ptr<Cell> &right) const;
        virtual bool opNeq(const std::unique_ptr<Cell> &right) const;
        int value;
    };

    class BoolCell : public Cell
    {
      public:
        BoolCell(bool v) : value(v) {}
        virtual bool opG(const std::unique_ptr<Cell> &right) const;
        virtual bool opL(const std::unique_ptr<Cell> &right) const;
        virtual bool opEq(const std::unique_ptr<Cell> &right) const;
        virtual bool opGeq(const std::unique_ptr<Cell> &right) const;
        virtual bool opLeq(const std::unique_ptr<Cell> &right) const;
        virtual bool opNeq(const std::unique_ptr<Cell> &right) const;
        virtual std::unique_ptr<Cell> opOr(const std::unique_ptr<Cell> &right) const;
        virtual std::unique_ptr<Cell> opAnd(const std::unique_ptr<Cell> &right) const;
        virtual std::unique_ptr<Cell> opNot() const;
        bool value;
    };

    class StringCell : public Cell
    {
      public:
        StringCell(std::string v) : value(v) {}
        virtual std::unique_ptr<Cell> opPlus(const std::unique_ptr<Cell> &right) const;
        virtual bool opG(const std::unique_ptr<Cell> &right) const;
        virtual bool opL(const std::unique_ptr<Cell> &right) const;
        virtual bool opEq(const std::unique_ptr<Cell> &right) const;
        virtual bool opGeq(const std::unique_ptr<Cell> &right) const;
        virtual bool opLeq(const std::unique_ptr<Cell> &right) const;
        virtual bool opNeq(const std::unique_ptr<Cell> &right) const;
        virtual int opAbs() const;
        std::string value;
    };

    class ByteArrayCell : public Cell
    {
      public:
        ByteArrayCell(int size, std::vector<int8_t> v) : value(v), sz(size) {}
        virtual bool opG(const std::unique_ptr<Cell> &right) const;
        virtual bool opL(const std::unique_ptr<Cell> &right) const;
        virtual bool opEq(const std::unique_ptr<Cell> &right) const;
        virtual bool opGeq(const std::unique_ptr<Cell> &right) const;
        virtual bool opLeq(const std::unique_ptr<Cell> &right) const;
        virtual bool opNeq(const std::unique_ptr<Cell> &right) const;
        unsigned int sz;
        std::vector<int8_t> value;
    };

    class Creator
    {
      public:
        template <class... T> std::unique_ptr<Cell> generateCell(Types type, T... args);
    };

    class ColumnInfo
    {
      public:
        Types type;
        const unsigned int number;
        const std::any baseValue;
        const unsigned int attr;
    };

    class Row
    {
      public:
        const unsigned int sz;
        std::vector<std::unique_ptr<Cell>> v;
    };

    class Table
    {
      public:
        Table() = default;

      private:
        std::map<std::string, ColumnInfo> columns;
        std::list<Row> db;
        std::string name;

        Response createTable(std::vector<std::tuple<std::string, std::optional<std::any>, int>> info);
        Response insert(std::vector<std::any> row);
        Table select(std::vector<std::string> cols, Condition cond);
        Response update(Condition cond, std::vector<std::pair<std::string, Expression>> v);
        Response del(Condition cond);
    };

    Response createTable(std::string s, std::vector<std::tuple<std::string, std::optional<std::any>, int>> info);
    Response insert(std::string s, std::vector<std::any> row);
    Table select(std::string s, std::vector<std::string> cols, Condition cond);
    Response update(std::string s, Condition cond, std::vector<std::pair<std::string, Expression>> v);
    Response del(std::string s, Condition cond);
    Table join(std::string t1, std::string t2, Condition cond);

    std::map<std::string, Table> tables;
};