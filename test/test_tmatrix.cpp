#include "tmatrix.h"

#include <gtest.h>

TEST(TDynamicMatrix, can_create_matrix_with_positive_length)
{
	ASSERT_NO_THROW(TDynamicMatrix<int> m(5));
}

TEST(TDynamicMatrix, cant_create_too_large_matrix)
{
	ASSERT_ANY_THROW(TDynamicMatrix<int> m(MAX_MATRIX_SIZE + 1));
}

TEST(TDynamicMatrix, throws_when_create_matrix_with_negative_length)
{
	ASSERT_ANY_THROW(TDynamicMatrix<int> m(-5));
}

TEST(TDynamicMatrix, can_create_copied_matrix)
{
	TDynamicMatrix<int> m(5);

	ASSERT_NO_THROW(TDynamicMatrix<int> m1(m));
}

TEST(TDynamicMatrix, copied_matrix_is_equal_to_source_one)
{
	TDynamicMatrix<int> m1(13);

	m1[5][5] = 4;

	TDynamicMatrix<int> m2(m1);

	EXPECT_EQ(m1, m2);
}

TEST(TDynamicMatrix, copied_matrix_has_its_own_memory)
{
	TDynamicMatrix<int> m1(6), m2(m1);

	m2[4][1] = 3;

	EXPECT_NE(&m1[0], &m2[0]);
	EXPECT_NE(m1, m2);
}

TEST(TDynamicMatrix, can_get_size)
{
	TDynamicMatrix<int> m(13);

	EXPECT_EQ(13, m.size());
}

TEST(TDynamicMatrix, can_set_and_get_element)
{
	TDynamicMatrix<int> m(13);

	m[1][3] = 5;

	EXPECT_EQ(5, m[1][3]);
}

TEST(TDynamicMatrix, throws_when_set_element_with_negative_index)
{
	TDynamicMatrix<int> m(13);

	ASSERT_ANY_THROW(m[-1][3]);
	ASSERT_ANY_THROW(m[3][-1]);
}

TEST(TDynamicMatrix, throws_when_set_element_with_too_large_index)
{
	TDynamicMatrix<int> m(13);

	ASSERT_ANY_THROW(m[13][3]);
	ASSERT_ANY_THROW(m[3][13]);
}

TEST(TDynamicMatrix, can_assign_matrix_to_itself)
{
	TDynamicMatrix<int> m(13);

	ASSERT_NO_THROW(m = m);
}

TEST(TDynamicMatrix, can_assign_matrices_of_equal_size)
{
	TDynamicMatrix<int> m1(13), m2(13);

	m2[1][4] = 7;
	m2[6][9] = 3;

	m1 = m2;

	EXPECT_EQ(m1, m2);
}

TEST(TDynamicMatrix, assign_operator_change_matrix_size)
{
	TDynamicMatrix<int> m1(12), m2(13), m3(14);

	m1 = m2;
	m3 = m2;

	EXPECT_EQ(13, m1.size());
	EXPECT_EQ(13, m3.size());
}

TEST(TDynamicMatrix, can_assign_matrices_of_different_size)
{
	TDynamicMatrix<int> m1(6), m2(4);

	m1[5][2] = 1;
	m2[1][3] = 5;
	m2[2][3] = 7;

	m1 = m2;

	EXPECT_EQ(m1, m2);
}

TEST(TDynamicMatrix, compare_equal_matrices_return_true)
{
	TDynamicMatrix<int> m1(4), m2(4);

	m1[1][3] = 6;
	m1[2][1] = 1;

	m2 = m1;

	EXPECT_TRUE(m1 == m2);

	m2[3][0] = 9;

	EXPECT_FALSE(m1 == m2);
}

TEST(TDynamicMatrix, compare_matrix_with_itself_return_true)
{
	TDynamicMatrix<int> m(13);

	m[0][12] = 5;

	EXPECT_TRUE(m == m);
}

TEST(TDynamicMatrix, matrices_with_different_size_are_not_equal)
{
	TDynamicMatrix<int> m1(12), m2(13);

	EXPECT_FALSE(m1 == m2);
}

TEST(TDynamicMatrix, can_add_matrices_with_equal_size)
{
	TDynamicMatrix<int> m1(3), m2(3), expMtr(3);

	m1[0][1] = 4;
	m1[2][2] = 6;

	m2[1][2] = 1;
	m2[2][2] = 2;

	expMtr[0][1] = 4;
	expMtr[1][2] = 1;
	expMtr[2][2] = 8;

	EXPECT_EQ(expMtr, m1 + m2);
}

TEST(TDynamicMatrix, cant_add_matrices_with_not_equal_size)
{
	TDynamicVector<int> m1(12), m2(13);

	ASSERT_ANY_THROW(m1 + m2);
}

TEST(TDynamicMatrix, can_subtract_matrices_with_equal_size)
{
	TDynamicMatrix<int> m1(3), m2(3), expMtr(3);

	m1[0][0] = 2;
	m1[1][2] = 8;

	m2[1][2] = 3;
	m2[2][0] = -5;

	expMtr[0][0] = 2;
	expMtr[1][2] = 5;
	expMtr[2][0] = 5;

	EXPECT_EQ(expMtr, m1 - m2);
}

TEST(TDynamicMatrix, cant_subtract_matrixes_with_not_equal_size)
{
	TDynamicVector<int> m1(12), m2(13);

	ASSERT_ANY_THROW(m1 - m2);
}

