#include "gmock/gmock.h"
#include "../PayrollSystem/WeeklySchedule.h"

TEST(TestWeeklySchedule, IsPayDate_IsPayDateFri_ReturnTrue)
{
	Payroll::WeeklySchedule ws{};

	auto actual = ws.IsPayDate({8,1,2021});

	EXPECT_TRUE(actual);
}

TEST(TestWeeklySchedule, IsPayDate_IsNotPayDateThu_ReturnFalse)
{
	Payroll::WeeklySchedule ws{};

	auto actual = ws.IsPayDate({ 7,1,2021 });

	EXPECT_FALSE(actual);
}

TEST(TestWeeklySchedule, IsPayDate_IsNotPayDateSat_ReturnFalse)
{
	Payroll::WeeklySchedule ws{};

	auto actual = ws.IsPayDate({ 9,1,2021 });

	EXPECT_FALSE(actual);
}

TEST(TestWeeklySchedule, IsPayDate_IsNotPayDateSun_ReturnFalse)
{
	Payroll::WeeklySchedule ws{};

	auto actual = ws.IsPayDate({ 10,1,2021 });

	EXPECT_FALSE(actual);
}

TEST(TestWeeklySchedule, IsPayDate_IsNotPayDateWed_ReturnFalse)
{
	Payroll::WeeklySchedule ws{};

	auto actual = ws.IsPayDate({ 6,1,2021 });

	EXPECT_FALSE(actual);
}

TEST(TestWeeklySchedule, IsPayDate_IsNotPayDateTue_ReturnFalse)
{
	Payroll::WeeklySchedule ws{};

	auto actual = ws.IsPayDate({ 5,1,2021 });

	EXPECT_FALSE(actual);
}

TEST(TestWeeklySchedule, IsPayDate_IsNotPayDateMon_ReturnFalse)
{
	Payroll::WeeklySchedule ws{};

	auto actual = ws.IsPayDate({ 4,1,2021 });

	EXPECT_FALSE(actual);
}

TEST(TestWeeklySchedule, GetPayPeriodStartDate_Thursday_ReturnSaturdayWeekBefore)
{
	Payroll::WeeklySchedule ws{};

	auto actual = ws.GetPayPeriodStartDate({7,1,2021});
	
	Date expected{ 2,1,2021 };
	EXPECT_EQ(actual, expected);
}

TEST(TestWeeklySchedule, GetPayPeriodStartDate_Friday_ReturnSaturdayWeekBefore)
{
	Payroll::WeeklySchedule ws{};

	auto actual = ws.GetPayPeriodStartDate({ 8,1,2021 });
	
	Date expected{ 2,1,2021 };
	EXPECT_EQ(actual, expected);
}

TEST(TestWeeklySchedule, GetPayPeriodStartDate_Saturday_ReturnThisSaturday)
{
	Payroll::WeeklySchedule ws{};

	auto actual = ws.GetPayPeriodStartDate({ 9,1,2021 });
	
	Date expected{ 9,1,2021 };
	EXPECT_EQ(actual, expected);
}

TEST(TestWeeklySchedule, GetPayPeriodStartDate_LastDayFromFebInLeapYear_ReturnThisSaturday28th)
{
	Payroll::WeeklySchedule ws{};

	auto actual = ws.GetPayPeriodStartDate({ 1,3,2020 });
	
	Date expected{ 29,2,2020 };
	EXPECT_EQ(actual, expected);
}

TEST(TestWeeklySchedule, GetPayPeriodStartDate_LastDayFromFeb_Return27th)
{
	Payroll::WeeklySchedule ws{};

	auto actual = ws.GetPayPeriodStartDate({ 1,3,2021 });
	
	Date expected{ 27,2,2021 };
	EXPECT_EQ(actual, expected);
}

TEST(TestWeeklySchedule, GetPayPeriodStartDate_FirstOfNewYear_ReturnSatFromLastYear)
{
	Payroll::WeeklySchedule ws{};

	auto actual = ws.GetPayPeriodStartDate({ 1,1,2020 });
	
	Date expected{ 28,12,2019 };
	EXPECT_EQ(actual, expected);
}