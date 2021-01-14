#include "gmock/gmock.h"
#include "tooling.h"

TEST(TestPaydayTransaction, Execute_PaydayOnOneHouerlyEmployeeCommonExpensesWeeklySchedule_PaychecksFilledWithOnePaycheck)
{

	Payroll::Database db{};
	Payroll::Paychecks pcs{};
	Date d{8,1,2021};
	FillDatabase(db);
	Payroll::PaydayTransaction pdtrans{ &pcs, d, &db };

	pdtrans.Execute();

	auto epcs = GetExpectedPaychecksHourlyEmployee();
	EXPECT_EQ(pcs, epcs);
}

TEST(TestPaydayTransaction, Execute_PaydayOnOneHouerlyEmployeeCommonExpensesWeeklyScheduleMutlipleTC_PaychecksFilledWithOnePaycheck)
{

	Payroll::Database db{};
	Payroll::Paychecks pcs{};
	Date d{ 8,1,2021 };
	FillDatabaseWithMultipleTimeCardsOnOneDay(db);
	Payroll::PaydayTransaction pdtrans{ &pcs, d, &db };

	pdtrans.Execute();

	auto epcs = GetExpectedPaychecksHourlyEmployeeMultiTC();
	EXPECT_EQ(pcs, epcs);
}

TEST(TestPaydayTransaction, Execute_PaydayOnOneHouerlyEmployeeCommonExpensesWeeklyScheduleNoWorkDone_PaychecksFilledWithNoPaycheck)
{
	Payroll::Database db{};
	Payroll::Paychecks pcs{};
	Date d{ 8,1,2021 };
	FillDatabaseWithoutTimeCards(db);
	Payroll::PaydayTransaction pdtrans{ &pcs, d, &db };

	pdtrans.Execute();

	Payroll::Paychecks epcs{};
	EXPECT_EQ(pcs, epcs);
}

TEST(TestPaydayTransaction, Execute_PaydayOnOneSalariedEmployeeGermanExpensesMonthlySchedule_PaychecksFilledWithOnePaycheck)
{
	Payroll::Database db{};
	Payroll::Paychecks pcs{};
	Date d{ 31,1,2021 };
	FillDatabase(db);
	Payroll::PaydayTransaction pdtrans{ &pcs, d, &db };

	pdtrans.Execute();

	auto epcs = GetExpectedPaychecksSalariedEmployee();
	EXPECT_EQ(pcs, epcs);
}

TEST(TestPaydayTransaction, Execute_PaydayOnOneHourlyEmployeeCommonExpensesWeeklyScheduleOnLeapYearFeb_PaychecksFilledWithOnePaycheck)
{
	Payroll::Database db{};
	Payroll::Paychecks pcs{};
	Date d{ 29,2,2036 };
	int empid = 1;
	Payroll::AddHourlyEmployee(empid, "CG", 10.0 , &db ).Execute();
	Payroll::TimeCardTransaction({25,2,2036}, 5, empid, &db).Execute();
	Payroll::PaydayTransaction pdtrans{ &pcs, d, &db };

	pdtrans.Execute();

	Payroll::Paycheck pc{ {23,2,2036}, {29,2,2036} };
	pc.m_grossPay = 50.0;
	pc.m_netPay = 35.0;
	pc.m_deductions = 15.0;
	EXPECT_EQ(pcs[empid], pc);
}

TEST(TestPaydayTransaction, Execute_PaydayOnOneSalariedEmployeeGermanExpensesMonthlyScheduleOnLeapYearFeb_PaychecksFilledWithOnePaycheck)
{
	Payroll::Database db{};
	Payroll::Paychecks pcs{};
	Date d{ 29,2,2020 };
	int empid = 1;
	Payroll::AddSalariedEmployee(empid, "CG", 2500.0, &db).Execute();
	Payroll::ChangeGermanExpenses(empid, &db).Execute();
	Payroll::PaydayTransaction pdtrans{ &pcs, d, &db };

	pdtrans.Execute();

	Payroll::Paycheck pc{ {1,2,2020}, {29,2,2020} };
	pc.m_grossPay = 2500.0;
	pc.m_netPay = 1670.0;
	pc.m_deductions = 830.0;
	EXPECT_EQ(pcs[empid], pc);
}

TEST(TestPaydayTransaction, Execute_PaydayOnOneHourlyEmployeeCommonExpensesWeeklyScheduleNoLeapYearFeb_PaychecksFilledWithOnePaycheck)
{
	Payroll::Database db{};
	Payroll::Paychecks pcs{};
	Date d{ 28,2,2025 };
	int empid = 1;
	Payroll::AddHourlyEmployee(empid, "CG", 10.0, &db).Execute();
	Payroll::TimeCardTransaction({ 25,2,2025 }, 5, empid, &db).Execute();
	Payroll::PaydayTransaction pdtrans{ &pcs, d, &db };

	pdtrans.Execute();

	Payroll::Paycheck pc{ {22,2,2025}, {28,2,2025} };
	pc.m_grossPay = 50.0;
	pc.m_netPay = 35.0;
	pc.m_deductions = 15.0;
	EXPECT_EQ(pcs[empid], pc);
}

TEST(TestPaydayTransaction, Execute_PaydayOnOneSalariedEmployeeGermanExpensesMonthlyScheduleNoLeapYearFeb_PaychecksFilledWithOnePaycheck)
{
	Payroll::Database db{};
	Payroll::Paychecks pcs{};
	Date d{ 28,2,2021 };
	int empid = 1;
	Payroll::AddSalariedEmployee(empid, "CG", 2500.0, &db).Execute();
	Payroll::ChangeGermanExpenses(empid, &db).Execute();
	Payroll::PaydayTransaction pdtrans{ &pcs, d, &db };

	pdtrans.Execute();

	Payroll::Paycheck pc{ {1,2,2021}, {28,2,2021} };
	pc.m_grossPay = 2500.0;
	pc.m_netPay = 1670.0;
	pc.m_deductions = 830.0;
	EXPECT_EQ(pcs[empid], pc);
}

TEST(TestPaydayTransaction, Execute_NoPaydayOnOneSalariedEmployeeGermanExpensesMonthlyScheduleNoLeapYearFeb_PaychecksFilledWithNoPaycheck)
{
	Payroll::Database db{};
	Payroll::Paychecks pcs{};
	Date d{ 27,2,2021 };
	int empid = 1;
	Payroll::AddSalariedEmployee(empid, "CG", 2500.0, &db).Execute();
	Payroll::ChangeGermanExpenses(empid, &db).Execute();
	Payroll::PaydayTransaction pdtrans{ &pcs, d, &db };

	pdtrans.Execute();

	EXPECT_TRUE(pcs.size() == 0);
}

TEST(TestPaydayTransaction, Execute_PaydayOnOneHourlyEmployeeCommonExpensesWeeklyScheduleWeakOverYear_PaychecksFilledWithOnePaycheck)
{
	Payroll::Database db{};
	Payroll::Paychecks pcs{};
	Date d{ 1,1,2021 };
	int empid = 1;
	Payroll::AddHourlyEmployee(empid, "CG", 10.0, &db).Execute();
	Payroll::TimeCardTransaction({ 28,12,2020 }, 5, empid, &db).Execute();
	Payroll::PaydayTransaction pdtrans{ &pcs, d, &db };

	pdtrans.Execute();

	Payroll::Paycheck pc{ {26,12,2020}, {1,1,2021} };
	pc.m_grossPay = 50.0;
	pc.m_netPay = 35.0;
	pc.m_deductions = 15.0;
	EXPECT_EQ(pcs[empid], pc);
}

TEST(TestPaydayTransaction, Execute_PaydayOnOneHourlyEmployeeCommonExpensesWeeklyScheduleMutlipleTCDiffDays_PaychecksFilledWithOnePaycheck)
{
	Payroll::Database db{};
	Payroll::Paychecks pcs{};
	Date d{ 1,1,2021 };
	int empid = 1;
	Payroll::AddHourlyEmployee(empid, "CG", 10.0, &db).Execute();
	Payroll::TimeCardTransaction({ 27,12,2020 }, 5, empid, &db).Execute();
	Payroll::TimeCardTransaction({ 28,12,2020 }, 5, empid, &db).Execute();
	Payroll::PaydayTransaction pdtrans{ &pcs, d, &db };

	pdtrans.Execute();

	Payroll::Paycheck pc{ {26,12,2020}, {1,1,2021} };
	pc.m_grossPay = 100;
	pc.m_netPay = 70.0;
	pc.m_deductions = 30.0;
	EXPECT_EQ(pcs[empid], pc);
}

TEST(TestPaydayTransaction, Execute_PaydayOnOneHourlyEmployeeCommonExpensesWeeklyScheduleMutlipleTCSameDay_PaychecksFilledWithOnePaycheckSum)
{
	Payroll::Database db{};
	Payroll::Paychecks pcs{};
	Date d{ 1,1,2021 };
	int empid = 1;
	Payroll::AddHourlyEmployee(empid, "CG", 10.0, &db).Execute();
	Payroll::TimeCardTransaction({ 28,12,2020 }, 2, empid, &db).Execute();
	Payroll::TimeCardTransaction({ 28,12,2020 }, 3, empid, &db).Execute();
	Payroll::PaydayTransaction pdtrans{ &pcs, d, &db };

	pdtrans.Execute();

	Payroll::Paycheck pc{ {26,12,2020}, {1,1,2021} };
	pc.m_grossPay = 50.0;
	pc.m_netPay = 35.0;
	pc.m_deductions = 15.0;
	EXPECT_EQ(pcs[empid], pc);
}

TEST(TestPaydayTransaction, Execute_PaydayOnOneHourlyEmployeeCommonExpensesWeeklyScheduleMutlipleTCDiffDaysOvertime_PaychecksFilledWithOnePaycheck)
{
	Payroll::Database db{};
	Payroll::Paychecks pcs{};
	Date d{ 1,1,2021 };
	int empid = 1;
	Payroll::AddHourlyEmployee(empid, "CG", 10.0, &db).Execute();
	Payroll::TimeCardTransaction({ 27,12,2020 }, 10, empid, &db).Execute();
	Payroll::TimeCardTransaction({ 28,12,2020 }, 10, empid, &db).Execute();
	Payroll::PaydayTransaction pdtrans{ &pcs, d, &db };

	pdtrans.Execute();

	Payroll::Paycheck pc{ {26,12,2020}, {1,1,2021} };
	pc.m_grossPay = 220.0;
	pc.m_netPay = 154.0;
	pc.m_deductions = 66.0;
	EXPECT_EQ(pcs[empid], pc);
}

TEST(TestPaydayTransaction, Execute_PaydayOnOneHourlyEmployeeCommonExpensesWeeklyScheduleMutlipleTCSameDayOvertime_PaychecksFilledWithOnePaycheckSum)
{
	Payroll::Database db{};
	Payroll::Paychecks pcs{};
	Date d{ 1,1,2021 };
	int empid = 1;
	Payroll::AddHourlyEmployee(empid, "CG", 10.0, &db).Execute();
	Payroll::TimeCardTransaction({ 28,12,2020 }, 5, empid, &db).Execute();
	Payroll::TimeCardTransaction({ 28,12,2020 }, 5, empid, &db).Execute();
	Payroll::PaydayTransaction pdtrans{ &pcs, d, &db };

	pdtrans.Execute();

	Payroll::Paycheck pc{ {26,12,2020}, {1,1,2021} };
	pc.m_grossPay = 110.0;
	pc.m_netPay = 77.0;
	pc.m_deductions = 33.0;
	EXPECT_EQ(pcs[empid], pc);
}

TEST(TestPaydayTransaction, Execute_PaydayOnOneSalariedEmployeeGermanExpensesMonthlyScheduleLegacyExpenseClassy_PaychecksFilledWithOnePaycheck)
{
	Payroll::Database db{};
	Payroll::Paychecks pcs{};
	Date d{ 31,12,2000 };
	int empid = 1;
	Payroll::AddSalariedEmployee(empid, "CG", 2500.0, &db).Execute();
	Payroll::ChangeGermanExpenses(empid, &db).Execute();
	Payroll::PaydayTransaction pdtrans{ &pcs, d, &db };

	pdtrans.Execute();

	Payroll::Paycheck pc{ {1,12,2000}, {31,12,2000} };
	pc.m_grossPay = 2500.0;
	pc.m_netPay = 1670.0;
	pc.m_deductions = 830.0;
	EXPECT_EQ(pcs[empid], pc);
}

TEST(TestPaydayTransaction, Execute_PaydayOnOneSalariedEmployeeGermanExpensesMonthlyScheduleLegacyExpenseWellPayed_PaychecksFilledWithOnePaycheck)
{
	Payroll::Database db{};
	Payroll::Paychecks pcs{};
	Date d{ 31,12,2000 };
	int empid = 1;
	Payroll::AddSalariedEmployee(empid, "CG", 4000.0, &db).Execute();
	Payroll::ChangeGermanExpenses(empid, &db).Execute();
	Payroll::PaydayTransaction pdtrans{ &pcs, d, &db };

	pdtrans.Execute();

	Payroll::Paycheck pc{ {1,12,2000}, {31,12,2000} };
	pc.m_grossPay = 4000.0;
	pc.m_netPay = 2600.0;
	pc.m_deductions = 1400.0;
	EXPECT_EQ(pcs[empid], pc);
}

TEST(TestPaydayTransaction, Execute_PaydayOnOneSalariedEmployeeGermanExpensesMonthlyScheduleLegacyExpenseVeryWellPayed_PaychecksFilledWithOnePaycheck)
{
	Payroll::Database db{};
	Payroll::Paychecks pcs{};
	Date d{ 31,12,2000 };
	int empid = 1;
	Payroll::AddSalariedEmployee(empid, "CG", 10000.0, &db).Execute();
	Payroll::ChangeGermanExpenses(empid, &db).Execute();
	Payroll::PaydayTransaction pdtrans{ &pcs, d, &db };

	pdtrans.Execute();

	Payroll::Paycheck pc{ {1,12,2000}, {31,12,2000} };
	pc.m_grossPay = 10000.0;
	pc.m_netPay = 4592,0;
	pc.m_deductions = 5408.0;
	EXPECT_EQ(pcs[empid], pc);
}

TEST(TestPaydayTransaction, Execute_PaydayOnOneProvisionalEmployeeCommonExpensesBiweeklyScheduleWithOneProvision53rdWeek_PaychecksFilledWithOnePaycheck)
{
	Payroll::Database db{};
	Payroll::Paychecks pcs{};
	Date d{ 1,1,2021 };
	int empid = 1;
	Payroll::AddProvisionalEmployee(empid, "CG", 1000.0, 0.1, &db).Execute();
	Payroll::ReceiptTransaction({ 28,12,2020 }, 1000, empid, &db).Execute();
	Payroll::PaydayTransaction pdtrans{ &pcs, d, &db };

	pdtrans.Execute();

	Payroll::Paycheck pc{ {26,12,2020}, {1,1,2021} };
	pc.m_grossPay = 1100.0;
	pc.m_netPay = 770.0;
	pc.m_deductions = 330.0;
	EXPECT_EQ(pcs[empid], pc);
}

TEST(TestPaydayTransaction, Execute_PaydayOnOneProvisionalEmployeeCommonExpensesBiweeklyScheduleNoProvision_PaychecksFilledWithOnePaycheck)
{
	Payroll::Database db{};
	Payroll::Paychecks pcs{};
	Date d{ 1,1,2021 };
	int empid = 1;
	Payroll::AddProvisionalEmployee(empid, "CG", 1000.0, 0.1, &db).Execute();
	Payroll::PaydayTransaction pdtrans{ &pcs, d, &db };

	pdtrans.Execute();

	Payroll::Paycheck pc{ {26,12,2020}, {1,1,2021} };
	pc.m_grossPay = 1000.0;
	pc.m_netPay = 700.0;
	pc.m_deductions = 300.0;
	EXPECT_EQ(pcs[empid], pc);
}

TEST(TestPaydayTransaction, Execute_PaydayOnOneProvisionalEmployeeCommonExpensesBiweeklyScheduleSeveralProvisions_PaychecksFilledWithOnePaycheck)
{
	Payroll::Database db{};
	Payroll::Paychecks pcs{};
	Date d{ 1,1,2021 };
	int empid = 1;
	Payroll::AddProvisionalEmployee(empid, "CG", 1000.0, 0.1, &db).Execute();
	Payroll::ReceiptTransaction({ 28,12,2020 }, 1000, empid, &db).Execute();
	Payroll::ReceiptTransaction({ 29,12,2020 }, 1000, empid, &db).Execute();
	Payroll::ReceiptTransaction({ 27,12,2020 }, 1000, empid, &db).Execute();
	Payroll::PaydayTransaction pdtrans{ &pcs, d, &db };

	pdtrans.Execute();

	Payroll::Paycheck pc{ {26,12,2020}, {1,1,2021} };
	pc.m_grossPay = 1300.0;
	pc.m_netPay = 910.0;
	pc.m_deductions = 390.0;
	EXPECT_EQ(pcs[empid], pc);
}

TEST(TestPaydayTransaction, Execute_PaydayOnOneProvisionalEmployeeCommonExpensesBiweeklyScheduleSeveralProvisionsSameDay_PaychecksFilledWithOnePaycheck)
{
	Payroll::Database db{};
	Payroll::Paychecks pcs{};
	Date d{ 1,1,2021 };
	int empid = 1;
	Payroll::AddProvisionalEmployee(empid, "CG", 1000.0, 0.1, &db).Execute();
	Payroll::ReceiptTransaction({ 28,12,2020 }, 1000, empid, &db).Execute();
	Payroll::ReceiptTransaction({ 28,12,2020 }, 1000, empid, &db).Execute();
	Payroll::ReceiptTransaction({ 28,12,2020 }, 1000, empid, &db).Execute();
	Payroll::PaydayTransaction pdtrans{ &pcs, d, &db };

	pdtrans.Execute();

	Payroll::Paycheck pc{ {26,12,2020}, {1,1,2021} };
	pc.m_grossPay = 1300.0;
	pc.m_netPay = 910.0;
	pc.m_deductions = 390.0;
	EXPECT_EQ(pcs[empid], pc);
}

TEST(TestPaydayTransaction, Execute_NoPaydayOnOneProvisionalEmployeeCommonExpensesBiweeklyScheduleNoProvision_PaychecksFilledWithOnePaycheck)
{
	Payroll::Database db{};
	Payroll::Paychecks pcs{};
	Date d{ 2,1,2021 };
	int empid = 1;
	Payroll::AddProvisionalEmployee(empid, "CG", 1000.0, 0.1, &db).Execute();
	Payroll::PaydayTransaction pdtrans{ &pcs, d, &db };

	pdtrans.Execute();

	Payroll::Paycheck pc{ };
	EXPECT_EQ(pcs[empid], pc);
}

TEST(TestPaydayTransaction, Execute_PaydayOnOneProvisionalEmployeeCommonExpensesBiweeklyScheduleWithOneProvisionSecondWeek_PaychecksFilledWithOnePaycheck)
{
	Payroll::Database db{};
	Payroll::Paychecks pcs{};
	Date d{ 15,1,2021 };
	int empid = 1;
	Payroll::AddProvisionalEmployee(empid, "CG", 1000.0, 0.1, &db).Execute();
	Payroll::ReceiptTransaction({ 3,1,2021 }, 1000, empid, &db).Execute();
	Payroll::PaydayTransaction pdtrans{ &pcs, d, &db };

	pdtrans.Execute();

	Payroll::Paycheck pc{ {2,1,2021}, {15,1,2021} };
	pc.m_grossPay = 1100.0;
	pc.m_netPay = 770.0;
	pc.m_deductions = 330.0;
	EXPECT_EQ(pcs[empid], pc);
}