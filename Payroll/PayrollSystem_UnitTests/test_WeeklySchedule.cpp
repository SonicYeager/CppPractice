#include "gmock/gmock.h"
#include "../PayrollSystem/WeeklySchedule.h"

TEST(TestWeeklySchedule, IsPayDate_IsPayDate_ReturnTrue)
{
	Payroll::WeeklySchedule ws{};

	auto actual = ws.IsPayDate({8,1,2021});

	EXPECT_TRUE(actual);
}