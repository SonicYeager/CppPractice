#include "PayrollDatabase.h"
#include "AddSalariedEmployee.h"
#include "AddHourlyEmployee.h"
#include "PaydayTransaction.h"
#include "TimeCardTransaction.h"
#include "ChangeGermanExpenses.h"
#include <iostream>

void Fill(Payroll::Database*);
void Print(const Payroll::Paychecks&, Date);

int main(int argc, char* argv[])
{
	Date date(20, 5, 2019);
	if(argc > 1)
		date = Date::FromString(argv[1]);

	Payroll::Database database;
	Payroll::Paychecks paychecks;
	Fill(&database);

	Payroll::PaydayTransaction(&paychecks, date, &database).Execute();

	Print(paychecks, date);
	std::cin.get();
}


void Fill(Payroll::Database* db)
{
	Payroll::AddSalariedEmployee(1234, "Helena", 3000, db).Execute();
	Payroll::AddSalariedEmployee(520, "Emanuel Neuer", 1500, db).Execute();
	Payroll::AddSalariedEmployee(942, "Chef", 15300, db).Execute();
	Payroll::AddHourlyEmployee(235, "Tim", 50, db).Execute();
	Payroll::AddHourlyEmployee(236, "Tom", 60, db).Execute();
	Payroll::AddHourlyEmployee(237, "Manni", 40, db).Execute();
	Payroll::AddSalariedEmployee(255, "Kunze", 2000, db).Execute();
	Payroll::AddHourlyEmployee(738, "Kuno", 120, db).Execute();

	Payroll::ChangeGermanExpenses(1234, db).Execute();
	Payroll::ChangeGermanExpenses(942, db).Execute();
	Payroll::ChangeGermanExpenses(235, db).Execute();
	Payroll::ChangeGermanExpenses(237, db).Execute();
	Payroll::ChangeGermanExpenses(255, db).Execute();

	Payroll::TimeCardTransaction(Date(13, 5, 2019), 5, 235, db).Execute();
	Payroll::TimeCardTransaction(Date(19, 5, 2019), 3, 235, db).Execute();
	Payroll::TimeCardTransaction(Date(19, 5, 2019), 3, 235, db).Execute();
	Payroll::TimeCardTransaction(Date(16, 5, 2019), 6, 236, db).Execute();
	Payroll::TimeCardTransaction(Date(17, 5, 2019), 10, 236, db).Execute();
	Payroll::TimeCardTransaction(Date(18, 5, 2019), 4, 236, db).Execute();
	Payroll::TimeCardTransaction(Date(22, 5, 2019), 2, 237, db).Execute();
	Payroll::TimeCardTransaction(Date(21, 5, 2019), 8, 237, db).Execute();
	Payroll::TimeCardTransaction(Date(20, 5, 2019), 7, 237, db).Execute();
}

void Print(const Payroll::Paychecks& paychecks, Date date)
{
	std::cout << "Payout for " << Date::ToString(date) << '\n';
	for(const auto& idAndPaycheck : paychecks)
	{
		std::cout << "employee " << idAndPaycheck.first
				  << " get paid " << idAndPaycheck.second.m_grossPay << " (gross)"
				  << " - " << idAndPaycheck.second.m_deductions << " (deductions)"
				  << " = " << idAndPaycheck.second.m_netPay << " (net)"
				  << " for " << Date::DiffDays(idAndPaycheck.second.m_payPeriodStart, idAndPaycheck.second.m_payPeriodEnd) << " days\n";
	}
	std::cout << "finished" << std::endl;
}
