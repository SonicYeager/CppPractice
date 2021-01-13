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

TEST(TestWeeklySchedule, GetPayPeriodStartDate_Friday53rdWeek_ReturnSatFrom52ndWeekYearBefore)
{
	Payroll::BiweeklySchedule ws{};

	auto actual = ws.GetPayPeriodStartDate({ 1,1,2021 });

	Date expected{ 26,12,2020 };
	EXPECT_EQ(actual, expected);
}

TEST(TestWeeklySchedule, GetPayPeriodStartDate_Friday2ndWeek_ReturnSatFrom53rdWeek)
{
	Payroll::BiweeklySchedule ws{};

	auto actual = ws.GetPayPeriodStartDate({ 15,1,2021 });

	Date expected{ 2,1,2021 };
	EXPECT_EQ(actual, expected);
}