#include "gmock/gmock.h"
#include "Matrix3x3.h"

TEST(TestMatrix3x3, Constructor_Scalar_ReturnDiagonalMatrix)
{
	const Matrix3x3 actual(1.5);

	const Matrix3x3 expected(1.5, 0, 0, 0, 1.5, 0, 0, 0, 1.5);
	EXPECT_EQ(expected, actual);
}

TEST(TestMatrix3x3, Access_NonConstantScalar_ChangesMatrix)
{
	Matrix3x3 actual;

	actual[0][0] = 2.5;
	actual[0][1] = -25;
	actual[1][2] = 11.25;
	actual[2][0] = -5.75;

	const Matrix3x3 expected(2.5, -25, 0, 0, 1, 11.25, -5.75, 0, 1);
	EXPECT_EQ(expected, actual);
}

TEST(TestMatrix3x3, Access_ConstantVector_ReturnLine)
{
	const Matrix3x3 actual(1, 2.5, 3, 4, 5, 6, 7.75, 8, 9.25);

	EXPECT_EQ(Vec3f(1, 2.5, 3), actual[0]);
	EXPECT_EQ(Vec3f(7.75, 8, 9.25), actual[2]);
}

TEST(TestMatrix3x3, Scale_ValueGreateZero_ReturnScaledMatrix)
{
	Matrix3x3 actual(1, 2, 3, 4, 5, 6, 7, 8, 9);
	actual *= 1.5;

	const Matrix3x3 expected(1.5, 3, 4.5, 6, 7.5, 9, 10.5, 12, 13.5);
	EXPECT_EQ(expected, actual);
}

TEST(TestMatrix3x3, Transpose_FilledWithDifferentValues_ReturnTransposedMatrix)
{
	Matrix3x3 actual(1, 2.5, 3, 4, 5, 6, 7.75, 8, 9.25);
	actual = Transpose(actual);

	const Matrix3x3 expected(1, 4, 7.75, 2.5, 5, 8, 3, 6, 9.25);
	EXPECT_EQ(expected, actual);
}
