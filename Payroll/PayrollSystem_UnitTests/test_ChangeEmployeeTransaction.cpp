#include "gmock/gmock.h"
#include "../PayrollSystem/ChangeEmployeeTransaction.h"

class MockChangeEmployeeTransaction : Payroll::ChangeEmployeeTransaction
{
public:
	using Payroll::ChangeEmployeeTransaction::Execute;
	using Payroll::ChangeEmployeeTransaction::ChangeEmployeeTransaction;
	MOCK_METHOD(void, Change, (Payroll::Employee* e), (override));
};

TEST(TestChangeEmployeeTransaction, Execute_EmployeeExists_CallsChange)
{
	Payroll::Database db{};
	db.AddEmployee(1, std::make_unique<Payroll::Employee>( 1, "Bob" ));
	testing::StrictMock<MockChangeEmployeeTransaction> cetrans{1, &db};
	EXPECT_CALL(cetrans, Change(db.GetEmployee(1))).Times(testing::AtLeast(1));

	cetrans.Execute();
}

TEST(TestChangeEmployeeTransaction, Execute_EmployeeNotExists_NoCalls)
{
	Payroll::Database db{};
	db.AddEmployee(1, std::make_unique<Payroll::Employee>(1, "Bob"));
	testing::StrictMock<MockChangeEmployeeTransaction> cetrans{ 3, &db };
	EXPECT_CALL(cetrans, Change(db.GetEmployee(1))).Times(testing::AtLeast(0));

	cetrans.Execute();
}