#include "gmock/gmock.h"
#include "../PayrollSystem/ProvisionClassification.h"

TEST(TestProvisionClassification, CalculatePay_ZeroReceiptPerc10Sal1000_Return1000)
{
	Payroll::ProvisionClassification proc{ 10.0, 1000.0 };
	Payroll::Paycheck pc{ {1, 2, 2000 }, {3, 2, 2000 } };

	auto actual = proc.CalculatePay(pc);
	double expected = 1000.0;

	EXPECT_EQ(actual, expected);
}

TEST(TestHourlyClassification, CalculatePay_OneReceipt1000ReceiptPerc10Sal1000_Return1100)
{
	Payroll::ProvisionClassification proc{ 10.0, 1000.0 };
	Payroll::Paycheck pc{ {1, 2, 2000 }, {3, 2, 2000 } };
	Payroll::Receipt tc{ {2, 2, 2000 }, 1000.0 };
	proc.AddReceipt(tc);

	auto actual = proc.CalculatePay(pc);
	double expected = 1100.0;

	EXPECT_EQ(actual, expected);
}

TEST(TestHourlyClassification, CalculatePay_MultipleReceipts1000DiffDaysReceiptPerc10Sal1000_Return1300)
{
	Payroll::ProvisionClassification proc{ 10.0, 1000.0 };
	Payroll::Paycheck pc{ {1, 2, 2000 }, {5, 2, 2000 } };
	Payroll::Receipt tc{ {2, 2, 2000 }, 1000.0 };
	Payroll::Receipt tc2{ {3, 2, 2000 }, 1000.0 };
	Payroll::Receipt tc3{ {4, 2, 2000 }, 1000.0 };
	proc.AddReceipt(tc);
	proc.AddReceipt(tc2);
	proc.AddReceipt(tc3);

	auto actual = proc.CalculatePay(pc);
	double expected = 1300.0;

	EXPECT_EQ(actual, expected);
}

TEST(TestHourlyClassification, CalculatePay_MultipleReceipts1000SameDayReceiptPerc10Sal1000_Return1300)
{
	Payroll::ProvisionClassification proc{ 10.0, 1000.0 };
	Payroll::Paycheck pc{ {1, 2, 2000 }, {3, 2, 2000 } };
	Payroll::Receipt tc{ {2, 2, 2000 }, 1000.0 };
	Payroll::Receipt tc2{ {2, 2, 2000 }, 1000.0 };
	Payroll::Receipt tc3{ {2, 2, 2000 }, 1000.0 };
	proc.AddReceipt(tc);
	proc.AddReceipt(tc2);
	proc.AddReceipt(tc3);

	auto actual = proc.CalculatePay(pc);
	double expected = 1300.0;

	EXPECT_EQ(actual, expected);
}

