#include "gmock/gmock.h"
#include "../PayrollSystem/MonthlySchedule.h"

TEST(TestMonthlySchedule, IsPayDay_PayDay_ReturnTrue)
{
	Payroll::MonthlySchedule ms{};

	auto actual = ms.IsPayDate({31,1,2021});

	EXPECT_TRUE(actual);
}

TEST(TestMonthlySchedule, IsPayDay_NoPayDay_ReturnFalse)
{
	Payroll::MonthlySchedule ms{};

	auto actual = ms.IsPayDate({ 30,1,2021 });

	EXPECT_FALSE(actual);
}

TEST(TestMonthlySchedule, IsPayDay_PayDayOnLeapYear_ReturnTrue)
{
	Payroll::MonthlySchedule ms{};

	auto actual = ms.IsPayDate({ 28,2,2020 });

	EXPECT_TRUE(actual);
}

TEST(TestMonthlySchedule, IsPayDay_NoPayDayOnLeapYear_ReturnFalse)
{
	Payroll::MonthlySchedule ms{};

	auto actual = ms.IsPayDate({ 29,2,2020 });

	EXPECT_FALSE(actual);
}