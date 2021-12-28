// тесты для стека

#include "stack.h"
#include <gtest.h>


TEST(Stack, create_stack_positive)
{
	ASSERT_NO_THROW(Stack<int> st);
}
TEST(Stack, create_stack_null_size_negative)
{
	ASSERT_ANY_THROW(Stack<int> st(0));
}
TEST(Stack, push_element_positive)
{
	Stack<int> st;
	ASSERT_NO_THROW(st.push(6));
}
TEST(Stack, push_element_in_full_stack_positive)
{
	Stack<int> st(1);
	st.push(2); 
	st.push(7);
	EXPECT_EQ(7, st.get_end());
}
TEST(Stack, empty_positive)
{
	Stack<int> st;
	EXPECT_EQ(true, st.empty());
}
TEST(Stack, empty_negative)
{
	Stack<int> st;
	st.push(7);
	EXPECT_EQ(false, st.empty());
}
TEST(Stack, full_positive)
{
	Stack<int> st(1);
	st.push(7);
	EXPECT_EQ(true, st.full());
}
TEST(Stack, full_negative)
{
	Stack<int> st;
	EXPECT_EQ(false, st.full());
}
TEST(Stack, get_end_positive)
{
	Stack<int> st(1);
	st.push(7);
	EXPECT_EQ(7, st.get_end());
	EXPECT_EQ(false, st.empty());
}
TEST(Stack, pop_element_positive)
{
	Stack<int> st;
	st.push(7);
	EXPECT_EQ(7, st.pop());
	EXPECT_EQ(true, st.empty());
}
TEST(Stack, pop_from_empty_stack_negative)
{
	Stack<int> st;
	ASSERT_ANY_THROW(st.pop());
}
TEST(Stack, get_end_from_empty_stack_negative)
{
	Stack<int> st;
	ASSERT_ANY_THROW(st.get_end());
}