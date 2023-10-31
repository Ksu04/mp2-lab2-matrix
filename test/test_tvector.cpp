#include "tmatrix.h"

#include <gtest.h>

TEST(TDynamicVector, can_create_vector_with_positive_length)
{
	ASSERT_NO_THROW(TDynamicVector<int> v(5));
}

TEST(TDynamicVector, cant_create_too_large_vector)
{
	ASSERT_ANY_THROW(TDynamicVector<int> v(MAX_VECTOR_SIZE + 1));
}

TEST(TDynamicVector, throws_when_create_vector_with_negative_length)
{
	ASSERT_ANY_THROW(TDynamicVector<int> v(-5));
}

TEST(TDynamicVector, can_create_copied_vector)
{
	TDynamicVector<int> v(10);

	ASSERT_NO_THROW(TDynamicVector<int> v1(v));
}

TEST(TDynamicVector, copied_vector_is_equal_to_source_one)
{
	TDynamicVector<int> v(10);
	EXPECT_EQ(v, TDynamicVector<int>(v));
}

TEST(TDynamicVector, copied_vector_has_its_own_memory)
{
	TDynamicVector<int> v1(6), v2(v1);

	v2[4] = 3;

	EXPECT_NE(&v1[0], &v2[0]);
	EXPECT_NE(v1, v2);
}

TEST(TDynamicVector, can_get_size)
{
	TDynamicVector<int> v(4);

	EXPECT_EQ(4, v.size());
}

//TEST(TDynamicVector, can_set_and_get_element)
//{
//  TDynamicVector<int> v(4);
//  v[0] = 4;
//
//  EXPECT_EQ(4, v[0]);
//}

TEST(TDynamicVector, throws_when_set_element_with_negative_index)
{
	TDynamicVector<int> v(5);
	ASSERT_ANY_THROW(v[-1] = 1);
}

TEST(TDynamicVector, throws_when_set_element_with_too_large_index)
{
	TDynamicVector<int> v(5);
	ASSERT_ANY_THROW(v[9] = 1);
}

TEST(TDynamicVector, can_assign_vector_to_itself)
{
	TDynamicVector<int> v(13);

	ASSERT_NO_THROW(v = v);
}

TEST(TDynamicVector, can_assign_vectors_of_equal_size)
{
	TDynamicVector<int> v1(2), v2(2);

	v2[0] = 3;
	v2[1] = 1;

	//v1 = v2;
	ASSERT_NO_THROW(v1 = v2);
	//EXPECT_EQ(v1[0], v2[0]);
	//EXPECT_EQ(v1[1], v2[1]);
}

TEST(TDynamicVector, assign_operator_change_vector_size)
{
	TDynamicVector<int> v1(7), v2(13), v3(16);

	v1 = v2;
	v3 = v2;

	EXPECT_EQ(13, v1.size());
	EXPECT_EQ(13, v3.size());
}

TEST(TDynamicVector, can_assign_vectors_of_different_size)
{
	TDynamicVector<int> v1(4), v2(13);

	v2[0] = 3;
	v2[7] = 8;
	v2[12] = 1;

	v1 = v2;

	EXPECT_EQ(v1[0], v2[0]);
	EXPECT_EQ(v1[7], v2[7]);
	EXPECT_EQ(v1[12], v2[12]);
}

TEST(TDynamicVector, compare_equal_vectors_return_true)
{
	TDynamicVector<int> v1(4), v2(13);

	v2[4] = 6;
	v2[9] = 1;
	v2[10] = 2;

	v1 = v2;

	EXPECT_TRUE(v1 == v2);
	EXPECT_FALSE(v1 != v2);

	v2[0] = 4;

	EXPECT_TRUE(v1 != v2);
	EXPECT_FALSE(v1 == v2);
}

TEST(TDynamicVector, compare_vector_with_itself_return_true)
{
	TDynamicVector<int> v(4);

	v[0] = 13;

	EXPECT_TRUE(v == v);
	EXPECT_FALSE(v != v);
}

TEST(TDynamicVector, vectors_with_different_size_are_not_equal)
{
	TDynamicVector<int> v1(14), v2(13);

	EXPECT_FALSE(v1 == v2);
	EXPECT_TRUE(v1 != v2);
}

TEST(TDynamicVector, can_add_scalar_to_vector)
{
	TDynamicVector<int> v1(2), v2(2);

	v1[0] = 4;
	v1[1] = 6;
	v2[0] = 0;
	v2[1] = 5;

	v1 = v1 + 7;
	v2 = v2 + 4;

	EXPECT_EQ(11, v1[0]);
	EXPECT_EQ(13, v1[1]);
	EXPECT_EQ(4, v2[0]);
	EXPECT_EQ(9, v2[1]);
}

TEST(TDynamicVector, can_subtract_scalar_from_vector)
{
	TDynamicVector<int> v1(2), v2(2);

	v1[0] = 5;
	v1[1] = 3;
	v2[0] = 6;
	v2[1] = 8;

	v1 = v1 - 1;
	v2 = v2 - 4;

	EXPECT_EQ(4, v1[0]);
	EXPECT_EQ(2, v1[1]);
	EXPECT_EQ(2, v2[0]);
	EXPECT_EQ(4, v2[1]);
}

TEST(TDynamicVector, can_multiply_scalar_by_vector)
{
	TDynamicVector<int> v(2);

	v[0] = 1;
	v[1] = 6;
	v = v * 7;

	EXPECT_EQ(7, v[0]);
	EXPECT_EQ(42, v[1]);
}

TEST(TDynamicVector, can_add_vectors_with_equal_size)
{
	TDynamicVector<int> v1(2), v2(2), expVec(2);

	v1[0] = 4;
	v1[1] = 3;
	v2[1] = 7;

	expVec[0] = 4;
	expVec[1] = 10;

	EXPECT_EQ(expVec, v1 + v2);

	v1 = v1 + v2;

	EXPECT_EQ(expVec, v1);
}

TEST(TDynamicVector, cant_add_vectors_with_not_equal_size)
{
	TDynamicVector<int> v1(12), v2(13);

	ASSERT_ANY_THROW(v1 + v2);
}

TEST(TDynamicVector, can_subtract_vectors_with_equal_size)
{
	TDynamicVector<int> v1(2), v2(2), expVec(2);

	v1[0] = 4; // 40
	v2[0] = 3; // 37
	v2[1] = 7;

	expVec[0] = 1;
	expVec[1] = -7;

	EXPECT_EQ(expVec, v1 - v2);
}

TEST(TDynamicVector, cant_subtract_vectors_with_not_equal_size)
{
	TDynamicVector<int> v1(12), v2(13);

	ASSERT_ANY_THROW(v1 - v2);
}

TEST(TDynamicVector, can_multiply_vectors_with_equal_size)
{
	TDynamicVector<int> v1(2), v2(2);

	v1[0] = 1;
	v1[1] = 4;
	v2[0] = 7;
	v2[1] = 3;

	EXPECT_EQ(19, v1 * v2);
}

TEST(TDynamicVector, cant_multiply_vectors_with_not_equal_size)
{
	TDynamicVector<int> v1(10), v2(13);

	ASSERT_ANY_THROW(v1 * v2);
}

