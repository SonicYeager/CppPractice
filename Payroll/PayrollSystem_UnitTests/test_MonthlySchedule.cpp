#include "gmock/gmock.h"
#include "../PayrollSystem/MonthlySchedule.h"

TEST(TestMonthlySchedule, IsPayDay_PayDay_ReturnTrue)
{
	Payroll::MonthlySchedule ms{};

	auto actual = ms.IsPayDate({31,1,2021});

	EXPECT_TRUE(actual);
}

TEST(TestMonthlySchedule, IsPayDay_NoPayDay_ReturnTrue)
{
	Payroll::MonthlySchedule ms{};

	auto actual = ms.IsPayDate({ 30,1,2021 });

	EXPECT_FALSE(actual);
}