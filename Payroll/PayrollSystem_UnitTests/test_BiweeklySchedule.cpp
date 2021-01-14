#include "gmock/gmock.h"
#include "../PayrollSystem/BiweeklySchedule.h"

TEST(TestBiweeklySchedule, IsPayDate_IsPayDateFriInMidstNewYearsEve_ReturnTrue)
{
	Payroll::BiweeklySchedule ws{};

	auto actual = ws.IsPayDate({ 1,1,2021 }); //this week is handled as solo and the corresponding friday is payout

	EXPECT_TRUE(actual);
}

TEST(TestBiweeklySchedule, IsPayDate_IsPayDateFriSecondWeek_ReturnTrue)
{
	Payroll::BiweeklySchedule ws{};

	auto actual = ws.IsPayDate({ 15,1,2021 });

	EXPECT_TRUE(actual);
}

TEST(TestBiweeklySchedule, IsPayDate_IsNotPayDateFriThirdWeek_ReturnFalse)
{
	Payroll::BiweeklySchedule ws{};

	auto actual = ws.IsPayDate({ 22,1,2021 });

	EXPECT_FALSE(actual);
}

TEST(TestBiweeklySchedule, IsPayDate_IsNotPayDateWedThirdWeek_ReturnFalse)
{
	Payroll::BiweeklySchedule ws{};

	auto actual = ws.IsPayDate({ 20,1,2021 });

	EXPECT_FALSE(actual);
}

TEST(TestBiweeklySchedule, GetPayPeriodStartDate_Friday53rdWeek_ReturnSatFrom52ndWeekYearBefore)
{
	Payroll::BiweeklySchedule ws{};

	auto actual = ws.GetPayPeriodStartDate({ 1,1,2021 });

	Date expected{ 26,12,2020 };
	EXPECT_EQ(actual, expected);
}

TEST(TestBiweeklySchedule, GetPayPeriodStartDate_Friday2ndWeek_ReturnSatFrom53rdWeek)
{
	Payroll::BiweeklySchedule ws{};

	auto actual = ws.GetPayPeriodStartDate({ 15,1,2021 });

	Date expected{ 2,1,2021 };
	EXPECT_EQ(actual, expected);
}

TEST(TestBiweeklySchedule, GetPayPeriodStartDate_FirstDayNewYearThu_ReturnSatFromPreviousWeek)
{
	Payroll::BiweeklySchedule ws{};

	auto actual = ws.GetPayPeriodStartDate({ 1,1,2026 });

	Date expected{ 27,12,2025 };
	EXPECT_EQ(actual, expected);
}

TEST(TestBiweeklySchedule, GetPayPeriodStartDate_SatOf2Week_ReturnSameSat)
{
	Payroll::BiweeklySchedule ws{};

	auto actual = ws.GetPayPeriodStartDate({ 16,1,2021 });

	Date expected{ 16,1,2021 };
	EXPECT_EQ(actual, expected);
}

TEST(TestBiweeklySchedule, GetPayPeriodStartDate_SunOf2Week_ReturnPreviousSat)
{
	Payroll::BiweeklySchedule ws{};

	auto actual = ws.GetPayPeriodStartDate({ 17,1,2021 });

	Date expected{ 16,1,2021 };
	EXPECT_EQ(actual, expected);
}

TEST(TestBiweeklySchedule, GetPayPeriodStartDate_SatOf3Week_ReturnPreviousWeekSat)
{
	Payroll::BiweeklySchedule ws{};

	auto actual = ws.GetPayPeriodStartDate({ 22,1,2021 });

	Date expected{ 16,1,2021 };
	EXPECT_EQ(actual, expected);
}

TEST(TestBiweeklySchedule, GetPayPeriodStartDate_SunOf3Week_ReturnPreviousWeekSat)
{
	Payroll::BiweeklySchedule ws{};

	auto actual = ws.GetPayPeriodStartDate({ 23,1,2021 });

	Date expected{ 16,1,2021 };
	EXPECT_EQ(actual, expected);
}

TEST(TestBiweeklySchedule, GetPayPeriodStartDate_SatOf53Week_ReturnPreviousWeekSat)
{
	Payroll::BiweeklySchedule ws{};

	auto actual = ws.GetPayPeriodStartDate({ 2,1,2021 });

	Date expected{ 2,1,2021 };
	EXPECT_EQ(actual, expected);
}

TEST(TestBiweeklySchedule, GetPayPeriodStartDate_SunOf53Week_ReturnPreviousWeekSat)
{
	Payroll::BiweeklySchedule ws{};

	auto actual = ws.GetPayPeriodStartDate({ 3,1,2021 });

	Date expected{ 2,1,2021 };
	EXPECT_EQ(actual, expected);
}