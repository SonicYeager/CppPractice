#include "gmock/gmock.h"
#include "../PayrollSystem/PaydayTransaction.h"

#include "../PayrollSystem/HourlyClassification.h"
#include "../PayrollSystem/SalariedClassification.h"
#include "../PayrollSystem/WeeklySchedule.h"
#include "../PayrollSystem/MonthlySchedule.h"
#include "../PayrollSystem/CommonExpenses.h"
#include "../PayrollSystem/GermanExpenses.h"

namespace Payroll
{
	bool operator==(const Payroll::Paycheck& left, const Payroll::Paycheck& right)
	{
		return left.m_payPeriodStart == right.m_payPeriodStart
			&& left.m_payPeriodEnd == right.m_payPeriodEnd
			&& left.m_grossPay == right.m_grossPay
			&& left.m_netPay == right.m_netPay
			&& left.m_deductions == right.m_deductions;
	}

	bool operator==(const Payroll::Paychecks& left, const Payroll::Paychecks& right)
	{
		if (left.size() == right.size())
		{
			for (auto entry : left)
			{
				auto correspondingVal = right.find(entry.first);
				if (not (entry.second == correspondingVal->second))
					return false;
			}
		}
		else
			return false;
		return true;
	}

	std::ostream& operator<<(std::ostream& os, const Date& d)
	{
		return os << "{" << d.Day() << ", " << d.Month() << ", " << d.Year() << "}";
	}

	std::ostream& operator<<(std::ostream& os, const Paycheck& pc)
	{
		return os
			<< "{" << pc.m_payPeriodStart << ", "
			<< pc.m_payPeriodEnd << ", "
			<< pc.m_grossPay << ", "
			<< pc.m_deductions << ", "
			<< pc.m_netPay << "}";
	}

	std::ostream& operator<<(std::ostream& os, const Paychecks& pcs)
	{
		for(const auto& entry : pcs)
		{ 
			os << "{" << entry.first << ", " << entry.second << "}";
		}
		return os;
	}
}

void FillDatabase(Payroll::Database& db)
{
	std::unique_ptr<Payroll::Employee> e1 = std::make_unique<Payroll::Employee>(1, "V");
	Payroll::HourlyClassification hc{10.0};
	hc.AddTimeCard({ {2,1,2021}, 2.0 });
	e1->SetClassification(std::make_unique<Payroll::HourlyClassification>(hc));
	e1->SetSchedule(std::make_unique<Payroll::WeeklySchedule>());
	e1->SetExpenses(std::make_unique<Payroll::CommonExpenses>());

	std::unique_ptr<Payroll::Employee> e2 = std::make_unique<Payroll::Employee>(2, "Data");
	Payroll::SalariedClassification sc{ 2000.0 };
	e2->SetClassification(std::make_unique<Payroll::SalariedClassification>(sc));
	e2->SetSchedule(std::make_unique<Payroll::MonthlySchedule>());
	e2->SetExpenses(std::make_unique<Payroll::GermanExpenses>());
	db.AddEmployee(1, std::move(e1));
	db.AddEmployee(2, std::move(e2));
}

Payroll::Paychecks GetExpectedPaychecksHourlyEmployee()
{
	Payroll::Paycheck pc1{ {4,1,2021}, {8,1,2021} };
	pc1.m_grossPay = 20.0;
	pc1.m_netPay = 12.0;
	pc1.m_deductions = 6.0;
	Payroll::Paychecks pcs{ {1,{pc1}} };
	return pcs;
}

Payroll::Paychecks GetExpectedPaychecksSalariedEmployee()
{
	Payroll::Paycheck pc2{ {1,1,2021}, {31,1,2021} };
	pc2.m_grossPay = 2000.0;
	pc2.m_netPay = 1336.0;
	pc2.m_deductions = 664.0;
	Payroll::Paychecks pcs{ {2,{pc2}} };
	return pcs;
}

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