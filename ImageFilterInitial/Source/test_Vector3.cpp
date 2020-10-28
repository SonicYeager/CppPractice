#include "gmock/gmock.h"
#include "Vector3.h"

using Vec3 = Vector3<float>;

TEST(TestVector3, Constructor_Scalar_FilledWithScalar)
{
	const Vec3 actual(3);

	const Vec3 expected(3, 3, 3);
	EXPECT_EQ(expected, actual);
}

TEST(TestVector3, Access_NonConstantScalar_ChangesVector)
{
	Vec3 actual;

	actual[0] = 2;
	actual[1] = 11;
	actual[2] = -5;

	const Vec3 expected(2, 11, -5);
	EXPECT_EQ(expected, actual);
}

TEST(TestVector3, Access_ConstantScalar_ReturnScalar)
{
	const Vec3 actual(1, 2, 3);

	EXPECT_EQ(1, actual[0]);
	EXPECT_EQ(3, actual[2]);
}

TEST(TestVector3, Assignment_Scalar_ReturnFilledWithScalar)
{
	Vec3 actual(1, 2, 3);

	actual = 5;

	const Vec3 expected(5, 5, 5);
	EXPECT_EQ(expected, actual);
}

TEST(TestVector3, Scale_ValueBetweenZeroAndOne_DecreasedElementsValue)
{
	Vec3 actual(10, 20, 30);

	actual *= 0.5;

	const Vec3 expected(5, 10, 15);
	EXPECT_EQ(expected, actual);
}

TEST(TestVector3, Scale_GreaterOne_IncreaseElementsValue)
{
	Vec3 actual(10, 20, 30);

	actual *= 1.5;

	const Vec3 expected(15, 30, 45);
	EXPECT_EQ(expected, actual);
}
