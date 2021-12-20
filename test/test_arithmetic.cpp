// тесты польской записи

#include <gtest.h>
#include <../include/arithmetic.h>

#define EPS 1e-5

TEST(arithmetic, can_create_arithmetic)
{
	ASSERT_NO_THROW(Arithmetic a);
}
TEST(arithmetic, simple_sum_1)
{
	Arithmetic a;
	string s;
	s = "6+3";
	a.string_to_lexeme(s);
	a.term_to_polish();
	EXPECT_EQ(9.0, a.calculate());
}
TEST(arithmetic, simple_sum_2)
{
	Arithmetic a;
	string s;
	s = "-9+11+7";
	a.string_to_lexeme(s);
	a.term_to_polish();
	EXPECT_EQ(9.0, a.calculate());
}
TEST(arithmetic, all_op)
{
	Arithmetic a;
	string s;
	s = "-7.4+2.2/4.0+2.6*6.9";
	a.string_to_lexeme(s);
	a.term_to_polish();
	EXPECT_NEAR(11.09, a.calculate(), EPS);
}
TEST(arithmetic, simple_brackets_sequence)
{
	Arithmetic a;
	string s;
	s = "8.5*(5+7)";
	a.string_to_lexeme(s);
	a.term_to_polish();
	EXPECT_EQ(102, a.calculate());
}
TEST(arithmetic, unary_minus_without_brackets)
{
	Arithmetic a;
	string s;
	s = "5+-5";
	a.string_to_lexeme(s);
	a.term_to_polish();
	EXPECT_EQ(0, a.calculate());
}
TEST(arithmetic, unary_minus_with_division)
{
	Arithmetic a;
	string s;
	s = "5/-5";
	a.string_to_lexeme(s);
	a.term_to_polish();
	EXPECT_EQ(-1.0, a.calculate());
}
TEST(arithmetic, unary_minus_with_division_with_brackets)
{
	Arithmetic a;
	string s;
	s = "5/-(2+2)";
	a.string_to_lexeme(s);
	a.term_to_polish();
	EXPECT_EQ(-1.25, a.calculate());
}
TEST(arithmetic, unary_minus_with_brackets_more_complex)
{
	Arithmetic a;
	string s;
	s = "5+(2-3/6-3)";
	a.string_to_lexeme(s);
	a.term_to_polish();
	EXPECT_EQ(3.5, a.calculate());
}
TEST(arithmetic, lots_of_unary_minus)
{
	Arithmetic a;
	string s;
	s = "5-------5";
	a.string_to_lexeme(s);
	a.term_to_polish();
	EXPECT_EQ(0.0, a.calculate());
}

TEST(arithmetic, unary_minus_before_brackets)
{
	Arithmetic a;
	string s;
	s = "-(5+5)";
	a.string_to_lexeme(s);
	a.term_to_polish();
	EXPECT_EQ(-10.0, a.calculate());
}
TEST(arithmetic, throw_when_first_character_is_closing_bracket)
{
	Arithmetic a;
	string s;
	s = ")5+2";
	a.string_to_lexeme(s);
	ASSERT_ANY_THROW(a.term_to_polish());
}
TEST(arithmetic, throw_when_first_character_is_operation)
{
	string s = "/(5+5)";
	ASSERT_ANY_THROW(validation(s));
}
TEST(arithmetic, throw_when_opening_bracket_goes_after_number)
{
	string s = "5(4+5)";
	ASSERT_ANY_THROW(validation(s));
}
TEST(arithmetic, throw_wrong_amounts_of_brackets)
{
	Arithmetic a;
	string s;
	s = "(5+2))";
	a.string_to_lexeme(s);
	ASSERT_ANY_THROW(validation(s));
}
TEST(arithmetic, throw_operation_after_opening_bracket)
{
	Arithmetic a;
	string s;
	s = "2+5-(*5)";
	a.string_to_lexeme(s);
	ASSERT_ANY_THROW(validation(s));
}
TEST(arithmetic, no_throw_unary_minus_after_opening_bracket)
{
	Arithmetic a;
	string s;
	s = "3+1*-4";
	a.string_to_lexeme(s);
	ASSERT_NO_THROW(a.term_to_polish());
}
TEST(arithmetic, throw_last_character_is_operation)
{
	string s = "5+5*";
	ASSERT_ANY_THROW(validation(s));
}
TEST(arithmetic, throw_last_character_is_opening_bracket)
{
	string s = "5+5*(";
	ASSERT_ANY_THROW(validation(s));
}
TEST(arithmetic, division_by_zero)
{
	Arithmetic a;
	string s;
	s = "5.5/0.0";
	a.string_to_lexeme(s);
	a.term_to_polish();
	ASSERT_ANY_THROW(a.calculate());
}
TEST(arithmetic, too_many_dots)
{
	Arithmetic a;
	string s;
	s = "5/5.5.5";
	ASSERT_ANY_THROW(a.string_to_lexeme(s));
}