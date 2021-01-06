#include "gmock/gmock.h"
#include "../PayrollSystem/CommonExpenses.h"

TEST(TestCommonExpenses, CalculateDeductions_EmptyPaycheck_ReturnZero)
{
	Payroll::CommonExpenses cexpenses{};
	Payroll::Paycheck pc{};

	auto actual = cexpenses.CalculateDeductions(pc);

	EXPECT_EQ(actual, 0.0);
}