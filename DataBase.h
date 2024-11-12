#pragma once

#include <any>
#include <map>
#include <memory>
#include <string>
#include <vector>

class DataBase
{
  private:
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
    std::map<std::string, ColumnInfo> columns;
    std::vector<Row> db;
};