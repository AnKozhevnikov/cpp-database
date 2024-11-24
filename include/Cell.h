#pragma once

#include <memory>
#include <string>
#include <vector>

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
    virtual std::unique_ptr<Cell> opG(const std::unique_ptr<Cell> &right) const;
    virtual std::unique_ptr<Cell> opL(const std::unique_ptr<Cell> &right) const;
    virtual std::unique_ptr<Cell> opEq(const std::unique_ptr<Cell> &right) const;
    virtual std::unique_ptr<Cell> opGeq(const std::unique_ptr<Cell> &right) const;
    virtual std::unique_ptr<Cell> opLeq(const std::unique_ptr<Cell> &right) const;
    virtual std::unique_ptr<Cell> opNeq(const std::unique_ptr<Cell> &right) const;
    virtual std::unique_ptr<Cell> opAnd(const std::unique_ptr<Cell> &right) const;
    virtual std::unique_ptr<Cell> opOr(const std::unique_ptr<Cell> &right) const;
    virtual std::unique_ptr<Cell> opNot() const;
    virtual std::unique_ptr<Cell> opXor(const std::unique_ptr<Cell> &right) const;
    virtual std::unique_ptr<Cell> opAbs() const;
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
    virtual std::unique_ptr<Cell> opG(const std::unique_ptr<Cell> &right) const;
    virtual std::unique_ptr<Cell> opL(const std::unique_ptr<Cell> &right) const;
    virtual std::unique_ptr<Cell> opEq(const std::unique_ptr<Cell> &right) const;
    virtual std::unique_ptr<Cell> opGeq(const std::unique_ptr<Cell> &right) const;
    virtual std::unique_ptr<Cell> opLeq(const std::unique_ptr<Cell> &right) const;
    virtual std::unique_ptr<Cell> opNeq(const std::unique_ptr<Cell> &right) const;
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
    virtual std::unique_ptr<Cell> opG(const std::unique_ptr<Cell> &right) const;
    virtual std::unique_ptr<Cell> opL(const std::unique_ptr<Cell> &right) const;
    virtual std::unique_ptr<Cell> opEq(const std::unique_ptr<Cell> &right) const;
    virtual std::unique_ptr<Cell> opGeq(const std::unique_ptr<Cell> &right) const;
    virtual std::unique_ptr<Cell> opLeq(const std::unique_ptr<Cell> &right) const;
    virtual std::unique_ptr<Cell> opNeq(const std::unique_ptr<Cell> &right) const;
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
    virtual std::unique_ptr<Cell> opG(const std::unique_ptr<Cell> &right) const;
    virtual std::unique_ptr<Cell> opL(const std::unique_ptr<Cell> &right) const;
    virtual std::unique_ptr<Cell> opEq(const std::unique_ptr<Cell> &right) const;
    virtual std::unique_ptr<Cell> opGeq(const std::unique_ptr<Cell> &right) const;
    virtual std::unique_ptr<Cell> opLeq(const std::unique_ptr<Cell> &right) const;
    virtual std::unique_ptr<Cell> opNeq(const std::unique_ptr<Cell> &right) const;
    virtual std::unique_ptr<Cell> opAbs() const;
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
    virtual std::unique_ptr<Cell> opG(const std::unique_ptr<Cell> &right) const;
    virtual std::unique_ptr<Cell> opL(const std::unique_ptr<Cell> &right) const;
    virtual std::unique_ptr<Cell> opEq(const std::unique_ptr<Cell> &right) const;
    virtual std::unique_ptr<Cell> opGeq(const std::unique_ptr<Cell> &right) const;
    virtual std::unique_ptr<Cell> opLeq(const std::unique_ptr<Cell> &right) const;
    virtual std::unique_ptr<Cell> opNeq(const std::unique_ptr<Cell> &right) const;
    std::vector<int8_t> value;
};