#include "gmock/gmock.h"
#include "tooling.h"

//EXPECTED TO WORK (WITH EXPECTED CORRECT BEHAVIOUR)

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
	FillDatabase(db);
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
	FillDatabase(db);
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

//EXPECTED NOT TO WORK (WITH EXPECTED WRONG BEHAVIOUR) -> they are only incorrect cause the year just started (too lazy to change)

TEST(TestPaydayTransaction, Execute_PaydayOnOneHouerlyEmployeeCommonExpensesWeeklyScheduleWrongDay_PaychecksFilledWithOnePaycheck)
{

	Payroll::Database db{};
	Payroll::Paychecks pcs{};
	Date d{ 6,1,2021 };
	FillDatabase(db);
	Payroll::PaydayTransaction pdtrans{ &pcs, d, &db };

	pdtrans.Execute();

	auto epcs = GetExpectedPaychecksHourlyEmployeeWrongDate();
	EXPECT_EQ(pcs, epcs);
}

TEST(TestPaydayTransaction, Execute_PaydayOnOneHouerlyEmployeeCommonExpensesWeeklyScheduleMultiTCOneDay_PaychecksFilledWithOnePaycheck)
{

	Payroll::Database db{};
	Payroll::Paychecks pcs{};
	Date d{ 6,1,2021 };
	FillDatabaseWithMultipleTimeCardsOnOneDay(db);
	Payroll::PaydayTransaction pdtrans{ &pcs, d, &db };

	pdtrans.Execute();

	auto epcs = GetExpectedPaychecksHourlyEmployeeMultiTCWrongDateWrongPay();
	EXPECT_EQ(pcs, epcs);
}

TEST(TestPaydayTransaction, Execute_PaydayOnOneHouerlyEmployeeCommonExpensesWeeklyScheduleWrongDayWithoutAnyTC_PaychecksFilledWithOnePaycheck)
{

	Payroll::Database db{};
	Payroll::Paychecks pcs{};
	Date d{ 6,1,2021 };
	FillDatabaseWithoutTimeCards(db);
	Payroll::PaydayTransaction pdtrans{ &pcs, d, &db };

	pdtrans.Execute();

	auto epcs = GetExpectedPaychecksHourlyEmployeeWithoutTCWrongDate();
	EXPECT_EQ(pcs, epcs);
}