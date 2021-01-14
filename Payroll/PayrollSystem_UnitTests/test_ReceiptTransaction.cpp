#include "gmock/gmock.h"
#include "../PayrollSystem/ReceiptTransaction.h"
#include "../PayrollSystem/ProvisionClassification.h"

namespace Payroll
{
	bool operator== (const Receipt& left, const Receipt& right)
	{
		return left.GetDate() == right.GetDate() && left.GetRevenue() == right.GetRevenue();
	}
}

TEST(TestReceiptTransaction, Execute_EmployeeExistsProvisionClassificationExists_ExecuteReceiptIsAdded)
{
	Payroll::Database db{};
	std::unique_ptr<Payroll::Employee> emp = std::make_unique<Payroll::Employee>(1, "Crusher");
	emp->SetClassification(std::make_unique<Payroll::ProvisionClassification>(0.1, 1000.0));
	db.AddEmployee(1, std::move(emp));
	Payroll::ReceiptTransaction tctrans{ {1,1,2021}, 3.0, 1, &db };

	tctrans.Execute();

	auto e = db.GetEmployee(1);
	auto hc = dynamic_cast<Payroll::ProvisionClassification*>(e->GetClassification());
	Payroll::Receipt actualtc = hc->GetReceipt({ 1,1,2021 });
	Payroll::Receipt expectedtc{ {1,1,2021}, 3.0 };
	EXPECT_EQ(actualtc, expectedtc);
}

//not real testing below (i am aware | better solution not yet popping up in my head)
TEST(TestReceiptTransaction, Execute_EmployeeExistsProvisionClassificationNotExists_ExecuteReceiptIsNotAdded)
{
	Payroll::Database db{};
	std::unique_ptr<Payroll::Employee> emp = std::make_unique<Payroll::Employee>(1, "Crusher");
	db.AddEmployee(1, std::move(emp));
	Payroll::ReceiptTransaction tctrans{ {1,1,2021}, 3.0, 1, &db };

	tctrans.Execute();

	auto e = db.GetEmployee(1);
	auto hc = dynamic_cast<Payroll::ProvisionClassification*>(e->GetClassification());
	EXPECT_EQ(hc, nullptr);
}

TEST(TestReceiptTransaction, Execute_EmployeeNotExistsProvisionClassificationNotExists_ExecuteReceiptIsNotAdded)
{
	Payroll::Database db{};
	Payroll::ReceiptTransaction tctrans{ {1,1,2021}, 3.0, 1, &db };

	tctrans.Execute();

	auto e = db.GetEmployee(1);
	EXPECT_EQ(e, nullptr);
}