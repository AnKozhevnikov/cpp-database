#pragma once

#include <any>
#include <list>
#include <map>
#include <memory>
#include <optional>
#include <string>
#include <vector>

#define UNIQUE 1
#define AUTOINCREMENT 2
#define KEY 4

class DataBase
{
  public:
    auto query(std::string q);

  private:
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
        virtual std::unique_ptr<Cell> clone() = 0;
        virtual void inc();

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
        virtual std::unique_ptr<Cell> clone();

        IntCell(int v) : value(v)
        {
        }
        virtual void inc();
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
        virtual std::unique_ptr<Cell> clone();

        BoolCell(bool v) : value(v)
        {
        }
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
        virtual std::unique_ptr<Cell> clone();

        StringCell(std::string v) : value(v)
        {
        }
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
        virtual std::unique_ptr<Cell> clone();

        ByteArrayCell(int size, std::vector<int8_t> v) : value(v), sz(size)
        {
        }
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
        unsigned int number;
        std::optional<std::any> baseValue;
        unsigned int attr;

        friend class DataBase;
    };

    class Row
    {
      public:
        Row() = default;

        bool fits(Condition cond);

        unsigned int sz;
        std::vector<std::unique_ptr<Cell>> v;
    };

    class Table
    {
      public:
        Table() = default;
        Table(bool s) : status(s)
        {
        }

      private:
        std::map<std::string, ColumnInfo> columns;
        std::list<Row> rows;
        std::string name;

        bool status;

        Table createTable(std::vector<std::tuple<std::string, std::optional<std::any>, int>> info);
        Table insert(std::vector<std::optional<std::any>> row);

        friend class DataBase;
    };

    Table createTable(std::string s, std::vector<std::tuple<std::string, Types, std::optional<std::any>, int>> info);
    Table insert(std::string s, std::vector<std::optional<std::any>> row);
    
    std::map<std::string, Table> tables;
};