// тесты польской записи

#include <gtest.h>
#include <../include/arithmetic.h>

#define infel 1e-5

TEST(arithmetic, create_solver_positive)
{
	ASSERT_NO_THROW(Solver l);
}
TEST(arithmetic, sum1)
{
	Solver l;
	string str;
	str = "6+3";
	l.string_to_lexeme(str);
	l.lexeme_to_reverse();
	EXPECT_EQ(9.0, l.calculation());
}
TEST(arithmetic, sum2)
{
	Solver l;
	string str;
	str = "-9+11+7";
	l.string_to_lexeme(str);
	l.lexeme_to_reverse();
	EXPECT_EQ(9.0, l.calculation());
}
TEST(arithmetic, last_point_sum)
{
	Solver l;
	string str;
	str = "4.2+3.";
	l.string_to_lexeme(str);
	l.lexeme_to_reverse();
	EXPECT_NEAR(7.2, l.calculation(), infel);
}
TEST(arithmetic, operations)
{
	Solver l;
	string str;
	str = "-7.4+2.2/4.0+2.6*6.9";
	l.string_to_lexeme(str);
	l.lexeme_to_reverse();
	EXPECT_NEAR(11.09, l.calculation(), infel);
}
TEST(arithmetic, brackets_expression)
{
	Solver l;
	string str;
	str = "8.5*(5+7)";
	l.string_to_lexeme(str);
	l.lexeme_to_reverse();
	EXPECT_EQ(102, l.calculation());
}
TEST(arithmetic, unary_minus_without_brackets)
{
	Solver l;
	string str;
	str = "5+-5";
	l.string_to_lexeme(str);
	l.lexeme_to_reverse();
	EXPECT_EQ(0, l.calculation());
}
TEST(arithmetic, unary_minus_division)
{
	Solver l;
	string str;
	str = "5/-5";
	l.string_to_lexeme(str);
	l.lexeme_to_reverse();
	EXPECT_EQ(-1.0, l.calculation());
}
TEST(arithmetic, unary_minus_after_operation)
{
	Solver l;
	string str = "12*-12";
	l.string_to_lexeme(str);
	l.lexeme_to_reverse();
	EXPECT_EQ(-144, l.calculation());
}
TEST(arithmetic, unary_minus_after_opening_bracket)
{
	Solver l;
	string str = "12*(-12)";
	l.string_to_lexeme(str);
	l.lexeme_to_reverse();
	EXPECT_EQ(-144, l.calculation());
}
TEST(arithmetic, unary_minus_division_brackets)
{
	Solver l;
	string str;
	str = "5/-(2+2)";
	l.string_to_lexeme(str);
	l.lexeme_to_reverse();
	EXPECT_EQ(-1.25, l.calculation());
}
TEST(arithmetic, unary_minus_brackets)
{
	Solver l;
	string str;
	str = "5+(2-3/6-3)";
	l.string_to_lexeme(str);
	l.lexeme_to_reverse();
	EXPECT_EQ(3.5, l.calculation());
}
TEST(arithmetic, many_unary_minus)
{
	Solver l;
	string str;
	str = "5-------5";
	l.string_to_lexeme(str);
	l.lexeme_to_reverse();
	EXPECT_EQ(0.0, l.calculation());
}

TEST(arithmetic, unary_minus_before_brackets)
{
	Solver l;
	string str;
	str = "-(5+5)";
	l.string_to_lexeme(str);
	l.lexeme_to_reverse();
	EXPECT_EQ(-10.0, l.calculation());
}
TEST(arithmetic, first_closing_bracket_negative)
{
	Solver l;
	string str;
	str = ")5+2";
	l.string_to_lexeme(str);
	ASSERT_ANY_THROW(l.lexeme_to_reverse());
}
TEST(arithmetic, first_operation_negative)
{
	string str = "/(5+5)";
	ASSERT_ANY_THROW(validation(str));
}
TEST(arithmetic, operation_before_point_negative)
{
	string str = "5/.4";
	ASSERT_ANY_THROW(validation(str));
}
TEST(arithmetic, opening_bracket_after_number_negative)
{
	string str = "5(4+5)";
	ASSERT_ANY_THROW(validation(str));
}
TEST(arithmetic, brackets_negative)
{
	string str = "(5+2))";
	ASSERT_ANY_THROW(validation(str));
}
TEST(arithmetic, operation_after_opening_bracket_negative)
{
	string str = "2+5-(*5)";
	ASSERT_ANY_THROW(validation(str));
}
TEST(arithmetic, unary_minus_after_opening_bracket_positive)
{
	Solver l;
	string str = "3+1*(-4)";
	l.string_to_lexeme(str);
	ASSERT_NO_THROW(l.lexeme_to_reverse());
}
TEST(arithmetic, last_operation_negative)
{
	string str = "5+5*";
	ASSERT_ANY_THROW(validation(str));
}
TEST(arithmetic, last_opening_bracket_negative)
{
	string str = "5+5*(";
	ASSERT_ANY_THROW(validation(str));
}
TEST(arithmetic, division_by_zero_negative)
{
	Solver l;
	string str = "5.5/0.0";
	l.string_to_lexeme(str);
	l.lexeme_to_reverse();
	ASSERT_ANY_THROW(l.calculation());
}
TEST(arithmetic, many_points_neagtive)
{
	Solver l;
	string str = "5/5.5.5";
	ASSERT_ANY_THROW(l.string_to_lexeme(str));
}