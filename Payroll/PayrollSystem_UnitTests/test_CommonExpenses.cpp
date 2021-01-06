#include "gmock/gmock.h"
#include "../PayrollSystem/CommonExpenses.h"

TEST(TestCommonExpenses, CalculateDeductions_EmptyPaycheck_ReturnZero)
{
	Payroll::CommonExpenses cexpenses{};
	Payroll::Paycheck pc{};

	auto actual = cexpenses.CalculateDeductions(pc);

	EXPECT_EQ(actual, 0.0);
}

TEST(TestCommonExpenses, CalculateDeductions_Twothousand_ReturnSixhundred)
{
	Payroll::CommonExpenses cexpenses{};
	Payroll::Paycheck pc{};
	pc.m_grossPay = 2000.0;

	auto actual = cexpenses.CalculateDeductions(pc);

	EXPECT_EQ(actual, 600.0);
}

TEST(TestCommonExpenses, CalculateDeductions_1999dot99_Return599dot997)
{
	Payroll::CommonExpenses cexpenses{};
	Payroll::Paycheck pc{};
	pc.m_grossPay = 1999.99;

	auto actual = cexpenses.CalculateDeductions(pc);

	EXPECT_EQ(actual, 599.997);
}