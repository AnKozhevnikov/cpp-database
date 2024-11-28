#include "DataBase.h"
#include <gtest/gtest.h>

TEST(IntOps, Plus)
{
    std::unique_ptr<Cell> c1 = std::make_unique<IntCell>(5);
    std::unique_ptr<Cell> c2 = std::make_unique<IntCell>(10);
    std::unique_ptr<Cell> c3 = c1->opPlus(c2);
    EXPECT_EQ(std::any_cast<int>(c3->getValue()), 15);

    std::unique_ptr<Cell> c4 = std::make_unique<IntCell>(-5);
    std::unique_ptr<Cell> c5 = std::make_unique<IntCell>(10);
    std::unique_ptr<Cell> c6 = c4->opPlus(c5);
    EXPECT_EQ(std::any_cast<int>(c6->getValue()), 5);

    std::unique_ptr<Cell> c7 = std::make_unique<IntCell>(-5);
    std::unique_ptr<Cell> c8 = std::make_unique<IntCell>(-10);
    std::unique_ptr<Cell> c9 = c7->opPlus(c8);
    EXPECT_EQ(std::any_cast<int>(c9->getValue()), -15);
}

TEST(IntOps, Minus)
{
    std::unique_ptr<Cell> c1 = std::make_unique<IntCell>(5);
    std::unique_ptr<Cell> c2 = std::make_unique<IntCell>(10);
    std::unique_ptr<Cell> c3 = c1->opMinus(c2);
    EXPECT_EQ(std::any_cast<int>(c3->getValue()), -5);

    std::unique_ptr<Cell> c4 = std::make_unique<IntCell>(-5);
    std::unique_ptr<Cell> c5 = std::make_unique<IntCell>(10);
    std::unique_ptr<Cell> c6 = c4->opMinus(c5);
    EXPECT_EQ(std::any_cast<int>(c6->getValue()), -15);

    std::unique_ptr<Cell> c7 = std::make_unique<IntCell>(-5);
    std::unique_ptr<Cell> c8 = std::make_unique<IntCell>(-10);
    std::unique_ptr<Cell> c9 = c7->opMinus(c8);
    EXPECT_EQ(std::any_cast<int>(c9->getValue()), 5);
}

TEST(IntOps, Mult)
{
    std::unique_ptr<Cell> c1 = std::make_unique<IntCell>(5);
    std::unique_ptr<Cell> c2 = std::make_unique<IntCell>(10);
    std::unique_ptr<Cell> c3 = c1->opMult(c2);
    EXPECT_EQ(std::any_cast<int>(c3->getValue()), 50);

    std::unique_ptr<Cell> c4 = std::make_unique<IntCell>(-5);
    std::unique_ptr<Cell> c5 = std::make_unique<IntCell>(10);
    std::unique_ptr<Cell> c6 = c4->opMult(c5);
    EXPECT_EQ(std::any_cast<int>(c6->getValue()), -50);

    std::unique_ptr<Cell> c7 = std::make_unique<IntCell>(-5);
    std::unique_ptr<Cell> c8 = std::make_unique<IntCell>(-10);
    std::unique_ptr<Cell> c9 = c7->opMult(c8);
    EXPECT_EQ(std::any_cast<int>(c9->getValue()), 50);
}

TEST(IntOps, Div)
{
    std::unique_ptr<Cell> c1 = std::make_unique<IntCell>(50);
    std::unique_ptr<Cell> c2 = std::make_unique<IntCell>(10);
    std::unique_ptr<Cell> c3 = c1->opDiv(c2);
    EXPECT_EQ(std::any_cast<int>(c3->getValue()), 5);

    std::unique_ptr<Cell> c4 = std::make_unique<IntCell>(-50);
    std::unique_ptr<Cell> c5 = std::make_unique<IntCell>(10);
    std::unique_ptr<Cell> c6 = c4->opDiv(c5);
    EXPECT_EQ(std::any_cast<int>(c6->getValue()), -5);

    std::unique_ptr<Cell> c7 = std::make_unique<IntCell>(-50);
    std::unique_ptr<Cell> c8 = std::make_unique<IntCell>(-10);
    std::unique_ptr<Cell> c9 = c7->opDiv(c8);
    EXPECT_EQ(std::any_cast<int>(c9->getValue()), 5);
}

TEST(IntOps, Mod)
{
    std::unique_ptr<Cell> c1 = std::make_unique<IntCell>(50);
    std::unique_ptr<Cell> c2 = std::make_unique<IntCell>(10);
    std::unique_ptr<Cell> c3 = c1->opMod(c2);
    EXPECT_EQ(std::any_cast<int>(c3->getValue()), 0);

    std::unique_ptr<Cell> c4 = std::make_unique<IntCell>(-50);
    std::unique_ptr<Cell> c5 = std::make_unique<IntCell>(10);
    std::unique_ptr<Cell> c6 = c4->opMod(c5);
    EXPECT_EQ(std::any_cast<int>(c6->getValue()), 0);

    std::unique_ptr<Cell> c7 = std::make_unique<IntCell>(-50);
    std::unique_ptr<Cell> c8 = std::make_unique<IntCell>(-10);
    std::unique_ptr<Cell> c9 = c7->opMod(c8);
    EXPECT_EQ(std::any_cast<int>(c9->getValue()), 0);
}

TEST(IntOps, G)
{
    std::unique_ptr<Cell> c1 = std::make_unique<IntCell>(50);
    std::unique_ptr<Cell> c2 = std::make_unique<IntCell>(10);
    std::unique_ptr<Cell> c3 = c1->opG(c2);
    EXPECT_EQ(std::any_cast<bool>(c3->getValue()), true);

    std::unique_ptr<Cell> c4 = std::make_unique<IntCell>(-50);
    std::unique_ptr<Cell> c5 = std::make_unique<IntCell>(10);
    std::unique_ptr<Cell> c6 = c4->opG(c5);
    EXPECT_EQ(std::any_cast<bool>(c6->getValue()), false);

    std::unique_ptr<Cell> c7 = std::make_unique<IntCell>(-50);
    std::unique_ptr<Cell> c8 = std::make_unique<IntCell>(-10);
    std::unique_ptr<Cell> c9 = c7->opG(c8);
    EXPECT_EQ(std::any_cast<bool>(c9->getValue()), false);
}

TEST(IntOps, L)
{
    std::unique_ptr<Cell> c1 = std::make_unique<IntCell>(50);
    std::unique_ptr<Cell> c2 = std::make_unique<IntCell>(10);
    std::unique_ptr<Cell> c3 = c1->opL(c2);
    EXPECT_EQ(std::any_cast<bool>(c3->getValue()), false);

    std::unique_ptr<Cell> c4 = std::make_unique<IntCell>(-50);
    std::unique_ptr<Cell> c5 = std::make_unique<IntCell>(10);
    std::unique_ptr<Cell> c6 = c4->opL(c5);
    EXPECT_EQ(std::any_cast<bool>(c6->getValue()), true);

    std::unique_ptr<Cell> c7 = std::make_unique<IntCell>(-50);
    std::unique_ptr<Cell> c8 = std::make_unique<IntCell>(-10);
    std::unique_ptr<Cell> c9 = c7->opL(c8);
    EXPECT_EQ(std::any_cast<bool>(c9->getValue()), true);
}

TEST(IntOps, Eq)
{
    std::unique_ptr<Cell> c1 = std::make_unique<IntCell>(50);
    std::unique_ptr<Cell> c2 = std::make_unique<IntCell>(10);
    std::unique_ptr<Cell> c3 = c1->opEq(c2);
    EXPECT_EQ(std::any_cast<bool>(c3->getValue()), false);

    std::unique_ptr<Cell> c4 = std::make_unique<IntCell>(-50);
    std::unique_ptr<Cell> c5 = std::make_unique<IntCell>(-50);
    std::unique_ptr<Cell> c6 = c4->opEq(c5);
    EXPECT_EQ(std::any_cast<bool>(c6->getValue()), true);

    std::unique_ptr<Cell> c7 = std::make_unique<IntCell>(-50);
    std::unique_ptr<Cell> c8 = std::make_unique<IntCell>(-10);
    std::unique_ptr<Cell> c9 = c7->opEq(c8);
    EXPECT_EQ(std::any_cast<bool>(c9->getValue()), false);
}

TEST(IntOps, Geq)
{
    std::unique_ptr<Cell> c1 = std::make_unique<IntCell>(50);
    std::unique_ptr<Cell> c2 = std::make_unique<IntCell>(10);
    std::unique_ptr<Cell> c3 = c1->opGeq(c2);
    EXPECT_EQ(std::any_cast<bool>(c3->getValue()), true);

    std::unique_ptr<Cell> c4 = std::make_unique<IntCell>(-50);
    std::unique_ptr<Cell> c5 = std::make_unique<IntCell>(-50);
    std::unique_ptr<Cell> c6 = c4->opGeq(c5);
    EXPECT_EQ(std::any_cast<bool>(c6->getValue()), true);

    std::unique_ptr<Cell> c7 = std::make_unique<IntCell>(-50);
    std::unique_ptr<Cell> c8 = std::make_unique<IntCell>(-10);
    std::unique_ptr<Cell> c9 = c7->opGeq(c8);
    EXPECT_EQ(std::any_cast<bool>(c9->getValue()), false);
}

TEST(IntOps, Leq)
{
    std::unique_ptr<Cell> c1 = std::make_unique<IntCell>(50);
    std::unique_ptr<Cell> c2 = std::make_unique<IntCell>(10);
    std::unique_ptr<Cell> c3 = c1->opLeq(c2);
    EXPECT_EQ(std::any_cast<bool>(c3->getValue()), false);

    std::unique_ptr<Cell> c4 = std::make_unique<IntCell>(-50);
    std::unique_ptr<Cell> c5 = std::make_unique<IntCell>(-50);
    std::unique_ptr<Cell> c6 = c4->opLeq(c5);
    EXPECT_EQ(std::any_cast<bool>(c6->getValue()), true);

    std::unique_ptr<Cell> c7 = std::make_unique<IntCell>(-50);
    std::unique_ptr<Cell> c8 = std::make_unique<IntCell>(-10);
    std::unique_ptr<Cell> c9 = c7->opLeq(c8);
    EXPECT_EQ(std::any_cast<bool>(c9->getValue()), true);
}

TEST(IntOps, Neq)
{
    std::unique_ptr<Cell> c1 = std::make_unique<IntCell>(50);
    std::unique_ptr<Cell> c2 = std::make_unique<IntCell>(10);
    std::unique_ptr<Cell> c3 = c1->opNeq(c2);
    EXPECT_EQ(std::any_cast<bool>(c3->getValue()), true);

    std::unique_ptr<Cell> c4 = std::make_unique<IntCell>(-50);
    std::unique_ptr<Cell> c5 = std::make_unique<IntCell>(-50);
    std::unique_ptr<Cell> c6 = c4->opNeq(c5);
    EXPECT_EQ(std::any_cast<bool>(c6->getValue()), false);

    std::unique_ptr<Cell> c7 = std::make_unique<IntCell>(-50);
    std::unique_ptr<Cell> c8 = std::make_unique<IntCell>(-10);
    std::unique_ptr<Cell> c9 = c7->opNeq(c8);
    EXPECT_EQ(std::any_cast<bool>(c9->getValue()), true);
}

TEST(BoolOps, G)
{
    std::unique_ptr<Cell> c1 = std::make_unique<BoolCell>(true);
    std::unique_ptr<Cell> c2 = std::make_unique<BoolCell>(false);
    std::unique_ptr<Cell> c3 = c1->opG(c2);
    EXPECT_EQ(std::any_cast<bool>(c3->getValue()), true);

    std::unique_ptr<Cell> c4 = std::make_unique<BoolCell>(false);
    std::unique_ptr<Cell> c5 = std::make_unique<BoolCell>(true);
    std::unique_ptr<Cell> c6 = c4->opG(c5);
    EXPECT_EQ(std::any_cast<bool>(c6->getValue()), false);

    std::unique_ptr<Cell> c7 = std::make_unique<BoolCell>(true);
    std::unique_ptr<Cell> c8 = std::make_unique<BoolCell>(true);
    std::unique_ptr<Cell> c9 = c7->opG(c8);
    EXPECT_EQ(std::any_cast<bool>(c9->getValue()), false);
}

TEST(BoolOps, L)
{
    std::unique_ptr<Cell> c1 = std::make_unique<BoolCell>(true);
    std::unique_ptr<Cell> c2 = std::make_unique<BoolCell>(false);
    std::unique_ptr<Cell> c3 = c1->opL(c2);
    EXPECT_EQ(std::any_cast<bool>(c3->getValue()), false);

    std::unique_ptr<Cell> c4 = std::make_unique<BoolCell>(false);
    std::unique_ptr<Cell> c5 = std::make_unique<BoolCell>(true);
    std::unique_ptr<Cell> c6 = c4->opL(c5);
    EXPECT_EQ(std::any_cast<bool>(c6->getValue()), true);

    std::unique_ptr<Cell> c7 = std::make_unique<BoolCell>(true);
    std::unique_ptr<Cell> c8 = std::make_unique<BoolCell>(true);
    std::unique_ptr<Cell> c9 = c7->opL(c8);
    EXPECT_EQ(std::any_cast<bool>(c9->getValue()), false);
}

TEST(BoolOps, Eq)
{
    std::unique_ptr<Cell> c1 = std::make_unique<BoolCell>(true);
    std::unique_ptr<Cell> c2 = std::make_unique<BoolCell>(false);
    std::unique_ptr<Cell> c3 = c1->opEq(c2);
    EXPECT_EQ(std::any_cast<bool>(c3->getValue()), false);

    std::unique_ptr<Cell> c4 = std::make_unique<BoolCell>(false);
    std::unique_ptr<Cell> c5 = std::make_unique<BoolCell>(false);
    std::unique_ptr<Cell> c6 = c4->opEq(c5);
    EXPECT_EQ(std::any_cast<bool>(c6->getValue()), true);

    std::unique_ptr<Cell> c7 = std::make_unique<BoolCell>(true);
    std::unique_ptr<Cell> c8 = std::make_unique<BoolCell>(true);
    std::unique_ptr<Cell> c9 = c7->opEq(c8);
    EXPECT_EQ(std::any_cast<bool>(c9->getValue()), true);
}

TEST(BoolOps, Geq)
{
    std::unique_ptr<Cell> c1 = std::make_unique<BoolCell>(true);
    std::unique_ptr<Cell> c2 = std::make_unique<BoolCell>(false);
    std::unique_ptr<Cell> c3 = c1->opGeq(c2);
    EXPECT_EQ(std::any_cast<bool>(c3->getValue()), true);

    std::unique_ptr<Cell> c4 = std::make_unique<BoolCell>(false);
    std::unique_ptr<Cell> c5 = std::make_unique<BoolCell>(false);
    std::unique_ptr<Cell> c6 = c4->opGeq(c5);
    EXPECT_EQ(std::any_cast<bool>(c6->getValue()), true);

    std::unique_ptr<Cell> c7 = std::make_unique<BoolCell>(true);
    std::unique_ptr<Cell> c8 = std::make_unique<BoolCell>(true);
    std::unique_ptr<Cell> c9 = c7->opGeq(c8);
    EXPECT_EQ(std::any_cast<bool>(c9->getValue()), true);
}

TEST(BoolOps, Leq)
{
    std::unique_ptr<Cell> c1 = std::make_unique<BoolCell>(true);
    std::unique_ptr<Cell> c2 = std::make_unique<BoolCell>(false);
    std::unique_ptr<Cell> c3 = c1->opLeq(c2);
    EXPECT_EQ(std::any_cast<bool>(c3->getValue()), false);

    std::unique_ptr<Cell> c4 = std::make_unique<BoolCell>(false);
    std::unique_ptr<Cell> c5 = std::make_unique<BoolCell>(false);
    std::unique_ptr<Cell> c6 = c4->opLeq(c5);
    EXPECT_EQ(std::any_cast<bool>(c6->getValue()), true);

    std::unique_ptr<Cell> c7 = std::make_unique<BoolCell>(true);
    std::unique_ptr<Cell> c8 = std::make_unique<BoolCell>(true);
    std::unique_ptr<Cell> c9 = c7->opLeq(c8);
    EXPECT_EQ(std::any_cast<bool>(c9->getValue()), true);
}

TEST(BoolOps, Neq)
{
    std::unique_ptr<Cell> c1 = std::make_unique<BoolCell>(true);
    std::unique_ptr<Cell> c2 = std::make_unique<BoolCell>(false);
    std::unique_ptr<Cell> c3 = c1->opNeq(c2);
    EXPECT_EQ(std::any_cast<bool>(c3->getValue()), true);

    std::unique_ptr<Cell> c4 = std::make_unique<BoolCell>(false);
    std::unique_ptr<Cell> c5 = std::make_unique<BoolCell>(false);
    std::unique_ptr<Cell> c6 = c4->opNeq(c5);
    EXPECT_EQ(std::any_cast<bool>(c6->getValue()), false);

    std::unique_ptr<Cell> c7 = std::make_unique<BoolCell>(true);
    std::unique_ptr<Cell> c8 = std::make_unique<BoolCell>(true);
    std::unique_ptr<Cell> c9 = c7->opNeq(c8);
    EXPECT_EQ(std::any_cast<bool>(c9->getValue()), false);
}

TEST(BoolOps, And)
{
    std::unique_ptr<Cell> c1 = std::make_unique<BoolCell>(true);
    std::unique_ptr<Cell> c2 = std::make_unique<BoolCell>(false);
    std::unique_ptr<Cell> c3 = c1->opAnd(c2);
    EXPECT_EQ(std::any_cast<bool>(c3->getValue()), false);

    std::unique_ptr<Cell> c4 = std::make_unique<BoolCell>(false);
    std::unique_ptr<Cell> c5 = std::make_unique<BoolCell>(false);
    std::unique_ptr<Cell> c6 = c4->opAnd(c5);
    EXPECT_EQ(std::any_cast<bool>(c6->getValue()), false);

    std::unique_ptr<Cell> c7 = std::make_unique<BoolCell>(true);
    std::unique_ptr<Cell> c8 = std::make_unique<BoolCell>(true);
    std::unique_ptr<Cell> c9 = c7->opAnd(c8);
    EXPECT_EQ(std::any_cast<bool>(c9->getValue()), true);
}

TEST(BoolOps, Or)
{
    std::unique_ptr<Cell> c1 = std::make_unique<BoolCell>(true);
    std::unique_ptr<Cell> c2 = std::make_unique<BoolCell>(false);
    std::unique_ptr<Cell> c3 = c1->opOr(c2);
    EXPECT_EQ(std::any_cast<bool>(c3->getValue()), true);

    std::unique_ptr<Cell> c4 = std::make_unique<BoolCell>(false);
    std::unique_ptr<Cell> c5 = std::make_unique<BoolCell>(false);
    std::unique_ptr<Cell> c6 = c4->opOr(c5);
    EXPECT_EQ(std::any_cast<bool>(c6->getValue()), false);

    std::unique_ptr<Cell> c7 = std::make_unique<BoolCell>(true);
    std::unique_ptr<Cell> c8 = std::make_unique<BoolCell>(true);
    std::unique_ptr<Cell> c9 = c7->opOr(c8);
    EXPECT_EQ(std::any_cast<bool>(c9->getValue()), true);
}

TEST(BoolOps, Not)
{
    std::unique_ptr<Cell> c1 = std::make_unique<BoolCell>(true);
    std::unique_ptr<Cell> c2 = c1->opNot();
    EXPECT_EQ(std::any_cast<bool>(c2->getValue()), false);

    std::unique_ptr<Cell> c3 = std::make_unique<BoolCell>(false);
    std::unique_ptr<Cell> c4 = c3->opNot();
    EXPECT_EQ(std::any_cast<bool>(c4->getValue()), true);
}

TEST(BoolOps, Xor)
{
    std::unique_ptr<Cell> c1 = std::make_unique<BoolCell>(true);
    std::unique_ptr<Cell> c2 = std::make_unique<BoolCell>(false);
    std::unique_ptr<Cell> c3 = c1->opXor(c2);
    EXPECT_EQ(std::any_cast<bool>(c3->getValue()), true);

    std::unique_ptr<Cell> c4 = std::make_unique<BoolCell>(false);
    std::unique_ptr<Cell> c5 = std::make_unique<BoolCell>(false);
    std::unique_ptr<Cell> c6 = c4->opXor(c5);
    EXPECT_EQ(std::any_cast<bool>(c6->getValue()), false);

    std::unique_ptr<Cell> c7 = std::make_unique<BoolCell>(true);
    std::unique_ptr<Cell> c8 = std::make_unique<BoolCell>(true);
    std::unique_ptr<Cell> c9 = c7->opXor(c8);
    EXPECT_EQ(std::any_cast<bool>(c9->getValue()), false);
}

TEST(StringOps, G)
{
    std::unique_ptr<Cell> c1 = std::make_unique<StringCell>("Hello");
    std::unique_ptr<Cell> c2 = std::make_unique<StringCell>("World");
    std::unique_ptr<Cell> c3 = c1->opG(c2);
    EXPECT_EQ(std::any_cast<bool>(c3->getValue()), false);

    std::unique_ptr<Cell> c4 = std::make_unique<StringCell>("World");
    std::unique_ptr<Cell> c5 = std::make_unique<StringCell>("Hello");
    std::unique_ptr<Cell> c6 = c4->opG(c5);
    EXPECT_EQ(std::any_cast<bool>(c6->getValue()), true);

    std::unique_ptr<Cell> c7 = std::make_unique<StringCell>("Hello");
    std::unique_ptr<Cell> c8 = std::make_unique<StringCell>("Hello");
    std::unique_ptr<Cell> c9 = c7->opG(c8);
    EXPECT_EQ(std::any_cast<bool>(c9->getValue()), false);
}

TEST(StringOps, L)
{
    std::unique_ptr<Cell> c1 = std::make_unique<StringCell>("Hello");
    std::unique_ptr<Cell> c2 = std::make_unique<StringCell>("World");
    std::unique_ptr<Cell> c3 = c1->opL(c2);
    EXPECT_EQ(std::any_cast<bool>(c3->getValue()), true);

    std::unique_ptr<Cell> c4 = std::make_unique<StringCell>("World");
    std::unique_ptr<Cell> c5 = std::make_unique<StringCell>("Hello");
    std::unique_ptr<Cell> c6 = c4->opL(c5);
    EXPECT_EQ(std::any_cast<bool>(c6->getValue()), false);

    std::unique_ptr<Cell> c7 = std::make_unique<StringCell>("Hello");
    std::unique_ptr<Cell> c8 = std::make_unique<StringCell>("Hello");
    std::unique_ptr<Cell> c9 = c7->opL(c8);
    EXPECT_EQ(std::any_cast<bool>(c9->getValue()), false);
}

TEST(StringOps, Eq)
{
    std::unique_ptr<Cell> c1 = std::make_unique<StringCell>("Hello");
    std::unique_ptr<Cell> c2 = std::make_unique<StringCell>("World");
    std::unique_ptr<Cell> c3 = c1->opEq(c2);
    EXPECT_EQ(std::any_cast<bool>(c3->getValue()), false);

    std::unique_ptr<Cell> c4 = std::make_unique<StringCell>("World");
    std::unique_ptr<Cell> c5 = std::make_unique<StringCell>("World");
    std::unique_ptr<Cell> c6 = c4->opEq(c5);
    EXPECT_EQ(std::any_cast<bool>(c6->getValue()), true);

    std::unique_ptr<Cell> c7 = std::make_unique<StringCell>("Hello");
    std::unique_ptr<Cell> c8 = std::make_unique<StringCell>("Hello");
    std::unique_ptr<Cell> c9 = c7->opEq(c8);
    EXPECT_EQ(std::any_cast<bool>(c9->getValue()), true);
}

TEST(StringOps, Geq)
{
    std::unique_ptr<Cell> c1 = std::make_unique<StringCell>("Hello");
    std::unique_ptr<Cell> c2 = std::make_unique<StringCell>("World");
    std::unique_ptr<Cell> c3 = c1->opGeq(c2);
    EXPECT_EQ(std::any_cast<bool>(c3->getValue()), false);

    std::unique_ptr<Cell> c4 = std::make_unique<StringCell>("World");
    std::unique_ptr<Cell> c5 = std::make_unique<StringCell>("World");
    std::unique_ptr<Cell> c6 = c4->opGeq(c5);
    EXPECT_EQ(std::any_cast<bool>(c6->getValue()), true);

    std::unique_ptr<Cell> c7 = std::make_unique<StringCell>("Hello");
    std::unique_ptr<Cell> c8 = std::make_unique<StringCell>("Hello");
    std::unique_ptr<Cell> c9 = c7->opGeq(c8);
    EXPECT_EQ(std::any_cast<bool>(c9->getValue()), true);
}

TEST(StringOps, Leq)
{
    std::unique_ptr<Cell> c1 = std::make_unique<StringCell>("Hello");
    std::unique_ptr<Cell> c2 = std::make_unique<StringCell>("World");
    std::unique_ptr<Cell> c3 = c1->opLeq(c2);
    EXPECT_EQ(std::any_cast<bool>(c3->getValue()), true);

    std::unique_ptr<Cell> c4 = std::make_unique<StringCell>("World");
    std::unique_ptr<Cell> c5 = std::make_unique<StringCell>("World");
    std::unique_ptr<Cell> c6 = c4->opLeq(c5);
    EXPECT_EQ(std::any_cast<bool>(c6->getValue()), true);

    std::unique_ptr<Cell> c7 = std::make_unique<StringCell>("Hello");
    std::unique_ptr<Cell> c8 = std::make_unique<StringCell>("Hello");
    std::unique_ptr<Cell> c9 = c7->opLeq(c8);
    EXPECT_EQ(std::any_cast<bool>(c9->getValue()), true);
}

TEST(StringOps, Neq)
{
    std::unique_ptr<Cell> c1 = std::make_unique<StringCell>("Hello");
    std::unique_ptr<Cell> c2 = std::make_unique<StringCell>("World");
    std::unique_ptr<Cell> c3 = c1->opNeq(c2);
    EXPECT_EQ(std::any_cast<bool>(c3->getValue()), true);

    std::unique_ptr<Cell> c4 = std::make_unique<StringCell>("World");
    std::unique_ptr<Cell> c5 = std::make_unique<StringCell>("World");
    std::unique_ptr<Cell> c6 = c4->opNeq(c5);
    EXPECT_EQ(std::any_cast<bool>(c6->getValue()), false);

    std::unique_ptr<Cell> c7 = std::make_unique<StringCell>("Hello");
    std::unique_ptr<Cell> c8 = std::make_unique<StringCell>("Hello");
    std::unique_ptr<Cell> c9 = c7->opNeq(c8);
    EXPECT_EQ(std::any_cast<bool>(c9->getValue()), false);
}

TEST(StringOps, Abs)
{
    std::unique_ptr<Cell> c1 = std::make_unique<StringCell>("Hello");
    std::unique_ptr<Cell> c2 = c1->opAbs();
    EXPECT_EQ(std::any_cast<int>(c2->getValue()), 5);
}

TEST(ByteArrayOps, G)
{
    std::unique_ptr<Cell> c1 = std::make_unique<ByteArrayCell>(std::vector<int8_t>{0x00});
    std::unique_ptr<Cell> c2 = std::make_unique<ByteArrayCell>(std::vector<int8_t>{0x01});
    std::unique_ptr<Cell> c3 = c1->opG(c2);
    EXPECT_EQ(std::any_cast<bool>(c3->getValue()), false);

    std::unique_ptr<Cell> c4 = std::make_unique<ByteArrayCell>(std::vector<int8_t>{0x01});
    std::unique_ptr<Cell> c5 = std::make_unique<ByteArrayCell>(std::vector<int8_t>{0x00});
    std::unique_ptr<Cell> c6 = c4->opG(c5);
    EXPECT_EQ(std::any_cast<bool>(c6->getValue()), true);

    std::unique_ptr<Cell> c7 = std::make_unique<ByteArrayCell>(std::vector<int8_t>{0x00});
    std::unique_ptr<Cell> c8 = std::make_unique<ByteArrayCell>(std::vector<int8_t>{0x00});
    std::unique_ptr<Cell> c9 = c7->opG(c8);
    EXPECT_EQ(std::any_cast<bool>(c9->getValue()), false);
}

TEST(ByteArrayOps, L)
{
    std::unique_ptr<Cell> c1 = std::make_unique<ByteArrayCell>(std::vector<int8_t>{0x00});
    std::unique_ptr<Cell> c2 = std::make_unique<ByteArrayCell>(std::vector<int8_t>{0x01});
    std::unique_ptr<Cell> c3 = c1->opL(c2);
    EXPECT_EQ(std::any_cast<bool>(c3->getValue()), true);

    std::unique_ptr<Cell> c4 = std::make_unique<ByteArrayCell>(std::vector<int8_t>{0x01});
    std::unique_ptr<Cell> c5 = std::make_unique<ByteArrayCell>(std::vector<int8_t>{0x00});
    std::unique_ptr<Cell> c6 = c4->opL(c5);
    EXPECT_EQ(std::any_cast<bool>(c6->getValue()), false);

    std::unique_ptr<Cell> c7 = std::make_unique<ByteArrayCell>(std::vector<int8_t>{0x00});
    std::unique_ptr<Cell> c8 = std::make_unique<ByteArrayCell>(std::vector<int8_t>{0x00});
    std::unique_ptr<Cell> c9 = c7->opL(c8);
    EXPECT_EQ(std::any_cast<bool>(c9->getValue()), false);
}

TEST(ByteArrayOps, Eq)
{
    std::unique_ptr<Cell> c1 = std::make_unique<ByteArrayCell>(std::vector<int8_t>{0x00});
    std::unique_ptr<Cell> c2 = std::make_unique<ByteArrayCell>(std::vector<int8_t>{0x01});
    std::unique_ptr<Cell> c3 = c1->opEq(c2);
    EXPECT_EQ(std::any_cast<bool>(c3->getValue()), false);

    std::unique_ptr<Cell> c4 = std::make_unique<ByteArrayCell>(std::vector<int8_t>{0x01});
    std::unique_ptr<Cell> c5 = std::make_unique<ByteArrayCell>(std::vector<int8_t>{0x01});
    std::unique_ptr<Cell> c6 = c4->opEq(c5);
    EXPECT_EQ(std::any_cast<bool>(c6->getValue()), true);

    std::unique_ptr<Cell> c7 = std::make_unique<ByteArrayCell>(std::vector<int8_t>{0x00});
    std::unique_ptr<Cell> c8 = std::make_unique<ByteArrayCell>(std::vector<int8_t>{0x00});
    std::unique_ptr<Cell> c9 = c7->opEq(c8);
    EXPECT_EQ(std::any_cast<bool>(c9->getValue()), true);
}

TEST(ByteArrayOps, Geq)
{
    std::unique_ptr<Cell> c1 = std::make_unique<ByteArrayCell>(std::vector<int8_t>{0x00});
    std::unique_ptr<Cell> c2 = std::make_unique<ByteArrayCell>(std::vector<int8_t>{0x01});
    std::unique_ptr<Cell> c3 = c1->opGeq(c2);
    EXPECT_EQ(std::any_cast<bool>(c3->getValue()), false);

    std::unique_ptr<Cell> c4 = std::make_unique<ByteArrayCell>(std::vector<int8_t>{0x01});
    std::unique_ptr<Cell> c5 = std::make_unique<ByteArrayCell>(std::vector<int8_t>{0x01});
    std::unique_ptr<Cell> c6 = c4->opGeq(c5);
    EXPECT_EQ(std::any_cast<bool>(c6->getValue()), true);

    std::unique_ptr<Cell> c7 = std::make_unique<ByteArrayCell>(std::vector<int8_t>{0x00});
    std::unique_ptr<Cell> c8 = std::make_unique<ByteArrayCell>(std::vector<int8_t>{0x00});
    std::unique_ptr<Cell> c9 = c7->opGeq(c8);
    EXPECT_EQ(std::any_cast<bool>(c9->getValue()), true);
}

TEST(ByteArrayOps, Leq)
{
    std::unique_ptr<Cell> c1 = std::make_unique<ByteArrayCell>(std::vector<int8_t>{0x00});
    std::unique_ptr<Cell> c2 = std::make_unique<ByteArrayCell>(std::vector<int8_t>{0x01});
    std::unique_ptr<Cell> c3 = c1->opLeq(c2);
    EXPECT_EQ(std::any_cast<bool>(c3->getValue()), true);

    std::unique_ptr<Cell> c4 = std::make_unique<ByteArrayCell>(std::vector<int8_t>{0x01});
    std::unique_ptr<Cell> c5 = std::make_unique<ByteArrayCell>(std::vector<int8_t>{0x00});
    std::unique_ptr<Cell> c6 = c4->opLeq(c5);
    EXPECT_EQ(std::any_cast<bool>(c6->getValue()), false);

    std::unique_ptr<Cell> c7 = std::make_unique<ByteArrayCell>(std::vector<int8_t>{0x00});
    std::unique_ptr<Cell> c8 = std::make_unique<ByteArrayCell>(std::vector<int8_t>{0x00});
    std::unique_ptr<Cell> c9 = c7->opLeq(c8);
    EXPECT_EQ(std::any_cast<bool>(c9->getValue()), true);
}

TEST(ByteArrayOps, Neq)
{
    std::unique_ptr<Cell> c1 = std::make_unique<ByteArrayCell>(std::vector<int8_t>{0x00});
    std::unique_ptr<Cell> c2 = std::make_unique<ByteArrayCell>(std::vector<int8_t>{0x01});
    std::unique_ptr<Cell> c3 = c1->opNeq(c2);
    EXPECT_EQ(std::any_cast<bool>(c3->getValue()), true);

    std::unique_ptr<Cell> c4 = std::make_unique<ByteArrayCell>(std::vector<int8_t>{0x01});
    std::unique_ptr<Cell> c5 = std::make_unique<ByteArrayCell>(std::vector<int8_t>{0x01});
    std::unique_ptr<Cell> c6 = c4->opNeq(c5);
    EXPECT_EQ(std::any_cast<bool>(c6->getValue()), false);

    std::unique_ptr<Cell> c7 = std::make_unique<ByteArrayCell>(std::vector<int8_t>{0x00});
    std::unique_ptr<Cell> c8 = std::make_unique<ByteArrayCell>(std::vector<int8_t>{0x00});
    std::unique_ptr<Cell> c9 = c7->opNeq(c8);
    EXPECT_EQ(std::any_cast<bool>(c9->getValue()), false);
}
