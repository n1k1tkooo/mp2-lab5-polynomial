#include "Polinom.cpp"
#include <gtest.h>

TEST(TPolinom, can_create_polinom)
{
  ASSERT_NO_THROW(TPolinom polinom);
}
TEST(TPolinom, can_create_polinom_with_argument)
{
	TPolinom polinom1;
	ASSERT_NO_THROW(TPolinom polinom2(polinom1));
}
TEST(TPolinom, can_create_polinom_with_monom)
{
	ASSERT_NO_THROW(TPolinom polinom("3x4y5z6"));
}
TEST(TPolinom, can_calculate_in_point_of_polinom)
{
	TPolinom polinom("3x4y5z6-2x5yz3");
	polinom.Convert();
	int result = polinom.CalculateInPoint(1, 1, 1);
	EXPECT_EQ(1, result);
}
TEST(TPolinom, can_compare_prefix_of_two_polinom)
{
	TPolinom polinom("3x4y5z6-2x5yz3");
	EXPECT_EQ("3x4y5z6-2x5yz3", polinom.GetPrefix());
}
TEST(TPolinom, can_compare_two_polinom_with_identical_value)
{
	TPolinom polinom1("3x4y5z6-2x5yz3");
	TPolinom polinom2("3x4y5z6-2x5yz3");
	EXPECT_TRUE(polinom1 == polinom2);
}
TEST(TPolinom, can_compare_two_polinom_with_different_value)
{
	TPolinom polinom1("3x4y5z6-2x5yz3");
	TPolinom polinom2("3x4y5z6+2x5yz3");
	EXPECT_FALSE(polinom1 == polinom2);
}
TEST(TPolinom, cant_sort_empty_polinom)
{
	TPolinom polinom;
	ASSERT_ANY_THROW(polinom.Sort());
}
TEST(TPolinom, cant_addition_with_empty_polinom)
{
	TPolinom polinom1("3x4y5z6-2x5yz3");
	TPolinom polinom2("");
	ASSERT_ANY_THROW(polinom1+polinom2);
}
TEST(TPolinom, cant_subtraction_with_empty_polinom)
{
	TPolinom polinom1("3x4y5z6-2x5yz3");
	TPolinom polinom2("");
	ASSERT_ANY_THROW(polinom1 - polinom2);
}
TEST(TPolinom, cant_multiplication_with_empty_polinom)
{
	TPolinom polinom1("3x4y5z6-2x5yz3");
	TPolinom polinom2("");
	ASSERT_ANY_THROW(polinom1 * polinom2);
}