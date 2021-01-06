#include "gmock/gmock.h"
#include "../PayrollSystem/GermanExpenses.h"

TEST(TestGermanExpenses, CalculateDeductions_2500Year2000_Return)
{
	Payroll::GermanExpenses gexp{};
	Payroll::Paycheck pc{};
	pc.m_grossPay = 2500.0;
	pc.m_payPeriodStart = Date(1,1,2000);

	auto actual = gexp.CalculateDeductions(pc);

	EXPECT_EQ(actual, 830.0);
}

TEST(TestGermanExpenses, CalculateDeductions_4000Year2000_Return1400)
{
	Payroll::GermanExpenses gexp{};
	Payroll::Paycheck pc{};
	pc.m_grossPay = 4000.0;
	pc.m_payPeriodStart = Date(1, 1, 2000);

	auto actual = gexp.CalculateDeductions(pc);

	EXPECT_EQ(actual, 1400.0);
}