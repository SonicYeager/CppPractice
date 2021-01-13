#include "gmock/gmock.h"
#include "../PayrollSystem/TimeCardTransaction.h"
#include "../PayrollSystem/HourlyClassification.h"

namespace Payroll
{
	bool operator== (const TimeCard& left, const TimeCard& right)
	{
		return left.GetDate() == right.GetDate() && left.GetHours() == right.GetHours();
	}
}

TEST(TestTimeCardTransaction, Execute_EmployeeExistsHourlyClassificationExists_ExecuteTimeCardIsAdded)
{
	Payroll::Database db{};
	std::unique_ptr<Payroll::Employee> emp = std::make_unique<Payroll::Employee>(1, "Crusher");
	emp->SetClassification(std::make_unique<Payroll::HourlyClassification>(9.0));
	db.AddEmployee(1, std::move(emp));
	Payroll::TimeCardTransaction tctrans{ {1,1,2021}, 3.0, 1, &db };

	tctrans.Execute();

	auto e = db.GetEmployee(1);
	auto hc = dynamic_cast<Payroll::HourlyClassification*>(e->GetClassification());
	Payroll::TimeCard actualtc = hc->GetTimeCard({ 1,1,2021 });
	Payroll::TimeCard expectedtc{ {1,1,2021}, 3.0 };
	EXPECT_EQ(actualtc, expectedtc);
}

//not real testing below (i am aware | better solution not yet popping up in my head)
TEST(TestTimeCardTransaction, Execute_EmployeeExistsHourlyClassificationNotExists_ExecuteTimeCardIsNotAdded)
{
	Payroll::Database db{};
	std::unique_ptr<Payroll::Employee> emp = std::make_unique<Payroll::Employee>(1, "Crusher");
	db.AddEmployee(1, std::move(emp));
	Payroll::TimeCardTransaction tctrans{ {1,1,2021}, 3.0, 1, &db };

	tctrans.Execute();

	auto e = db.GetEmployee(1);
	auto hc = dynamic_cast<Payroll::HourlyClassification*>(e->GetClassification());
	EXPECT_EQ(hc, nullptr);
}

TEST(TestTimeCardTransaction, Execute_EmployeeNotExistsHourlyClassificationNotExists_ExecuteTimeCardIsNotAdded)
{
	Payroll::Database db{};
	Payroll::TimeCardTransaction tctrans{ {1,1,2021}, 3.0, 1, &db };

	tctrans.Execute();

	auto e = db.GetEmployee(1);
	EXPECT_EQ(e, nullptr);
}