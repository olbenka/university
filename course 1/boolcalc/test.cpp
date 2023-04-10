#include "pch.h"
#include "../task5-boolcalc-olbenka/boolexpr.h"
#include "../task5-boolcalc-olbenka/formulaenode.h"
#include <string>
#include <iostream>

TEST(correctness, constructor) {
    EXPECT_NO_THROW(BooleanExpression("x1 > x2"));
    EXPECT_NO_THROW(BooleanExpression("x1 + x2 + x3"));
    EXPECT_NO_THROW(BooleanExpression("x1 ^ x2"));
    EXPECT_NO_THROW(BooleanExpression("x1 | x2"));
}
TEST(correctness, calc) {
    BooleanExpression a("1");
    BooleanExpression c("0");

    EXPECT_EQ(false, c.calc());
    EXPECT_EQ(true, a.calc());
}
TEST(correctness, cnf) {
    BooleanExpression a("x1>x2");
    BooleanExpression b("x1 + x2 + x3");
    BooleanExpression c("x1 | x2");

    BooleanExpression a1 = a.cnf();
    BooleanExpression b1 = b.cnf();
    BooleanExpression c1 = c.cnf();

    EXPECT_EQ("(~ (x1) v x2)", a1);
    EXPECT_EQ("(((((x1 v x2) v x3) & ((x1 v ~ (x2)) v ~ (x3))) & ((~ (x1) v x2) v ~ (x3))) & ((~ (x1) v ~ (x2)) v x3))", b1);
    EXPECT_EQ("(~ (x1) v ~ (x2))", c1);
}
TEST(correctness, dnf) {
    BooleanExpression a("x1>x2");
    BooleanExpression b("x1 + x2 + x3");
    BooleanExpression c("x1 | x2");

    BooleanExpression a1 = a.dnf();
    BooleanExpression b1 = b.dnf();
    BooleanExpression c1 = c.dnf();

    EXPECT_EQ("(((~ (x1) & ~ (x2)) v (~ (x1) & x2)) v (x1 & x2))", a1);
    EXPECT_EQ("(((((~ (x1) & ~ (x2)) & x3) v ((~ (x1) & x2) & ~ (x3))) v ((x1 & ~ (x2)) & ~ (x3))) v ((x1 & x2) & x3))", b1);
    EXPECT_EQ("(((~ (x1) & ~ (x2)) v (~ (x1) & x2)) v (x1 & ~ (x2)))", c1);
}

TEST(correctness, zhegalkin) {
    BooleanExpression a("x1>x2");
    BooleanExpression b("x1 + x2 + x3");
    BooleanExpression c("x1 | x2");

    BooleanExpression a1 = a.zhegalkin();
    BooleanExpression b1 = b.zhegalkin();
    BooleanExpression c1 = c.zhegalkin();

    EXPECT_EQ("((1 + x1) + (x1 & x2))", a1);
    EXPECT_EQ("(((0 + x3) + x2) + x1)", b1);
    EXPECT_EQ("(1 + (x1 & x2))", c1);
}

