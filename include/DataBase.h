#pragma once

#include <any>
#include <list>
#include <map>
#include <memory>
#include <optional>
#include <stdexcept>
#include <string>
#include <vector>

#define UNIQUE 1
#define AUTOINCREMENT 2
#define KEY 4

class DataBase
{
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
        virtual std::string toString();
        Cell(std::string s)
        {
        }
        Cell() = default;

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
        virtual std::string toString();
        IntCell(std::string s) : value(std::stoi(s))
        {
        }

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
        virtual std::string toString();
        BoolCell(std::string s) : value(s == "1")
        {
        }

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
        virtual std::string toString();

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
        virtual std::string toString();
        ByteArrayCell(std::string s);

        ByteArrayCell(std::vector<int8_t> v) : value(v)
        {
        }
        virtual bool opG(const std::unique_ptr<Cell> &right) const;
        virtual bool opL(const std::unique_ptr<Cell> &right) const;
        virtual bool opEq(const std::unique_ptr<Cell> &right) const;
        virtual bool opGeq(const std::unique_ptr<Cell> &right) const;
        virtual bool opLeq(const std::unique_ptr<Cell> &right) const;
        virtual bool opNeq(const std::unique_ptr<Cell> &right) const;
        std::vector<int8_t> value;
    };

    class Creator
    {
      public:
        std::unique_ptr<Cell> generateCell(Types type, std::any arg);
        std::optional<std::any> generateValue(Types type, std::string s);
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

        Row(const Row &other) = delete;                 // Disable copy constructor
        Row(Row &&other) noexcept = default;            // Enable move constructor
        Row &operator=(const Row &other) = delete;      // Disable copy assignment
        Row &operator=(Row &&other) noexcept = default; // Enable move assignment
    };

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

    Table createTable(std::string s, std::vector<std::tuple<std::string, Types, std::optional<std::any>, int>> info);
    Table insert(std::string s, std::vector<std::optional<std::any>> row);

    std::map<std::string, Table> tables;

  public:
    Table query(std::string q);
    void save(std::string path);
    void load(std::string path);
};