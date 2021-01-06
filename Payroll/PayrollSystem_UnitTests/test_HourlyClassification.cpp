#include "gmock/gmock.h"
#include "../PayrollSystem/HourlyClassification.h"

TEST(TestHourlyClassification, CalculatePay_Rate9OneTimeCard5HNoOvertime_Return45)
{
	Payroll::HourlyClassification hc{9.0};
	Payroll::Paycheck pc{ {1, 2, 2000 }, {3, 2, 2000 } };
	Payroll::TimeCard tc{ {2, 2, 2000 }, 5.0 };
	hc.AddTimeCard(tc);

	auto actual = hc.CalculatePay(pc);
	double expected = 45.0;

	EXPECT_EQ(actual, expected);
}

TEST(TestHourlyClassification, CalculatePay_Rate9OneTimeCard9HOvertime_Return85k5)
{
	Payroll::HourlyClassification hc{ 9.0 };
	Payroll::Paycheck pc{ {1, 2, 2000 }, {3, 2, 2000 } };
	Payroll::TimeCard tc{ {2, 2, 2000 }, 9.0 };
	hc.AddTimeCard(tc);

	auto actual = hc.CalculatePay(pc);
	double expected = 85.5;

	EXPECT_EQ(actual, expected);
}

TEST(TestHourlyClassification, CalculatePay_Rate9MultipleTimeCard5HNoOvertime_Return90)
{
	Payroll::HourlyClassification hc{ 9.0 };
	Payroll::Paycheck pc{ {1, 2, 2000 }, {4, 2, 2000 } };
	Payroll::TimeCard tc{ {2, 2, 2000 }, 5.0 };
	Payroll::TimeCard tc{ {3, 2, 2000 }, 5.0 };
	hc.AddTimeCard(tc);

	auto actual = hc.CalculatePay(pc);
	double expected = 90.0;

	EXPECT_EQ(actual, expected);
}

TEST(TestHourlyClassification, CalculatePay_Rate9MultipleTimeCard9HOvertime_Return171)
{
	Payroll::HourlyClassification hc{ 9.0 };
	Payroll::Paycheck pc{ {1, 2, 2000 }, {4, 2, 2000 } };
	Payroll::TimeCard tc{ {2, 2, 2000 }, 9.0 };
	Payroll::TimeCard tc{ {3, 2, 2000 }, 9.0 };
	hc.AddTimeCard(tc);

	auto actual = hc.CalculatePay(pc);
	double expected = 171.0;

	EXPECT_EQ(actual, expected);
}