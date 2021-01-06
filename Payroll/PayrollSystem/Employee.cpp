#include "Employee.h"
#include "CommonExpenses.h"

namespace Payroll
{
	Employee::Employee(int id, const std::string& name)
		: m_id(id)
		, m_name(name)
		, m_expenses(new CommonExpenses)
	{}

	std::string Employee::GetName() const
	{
		return m_name;
	}

	PaymentClassification* Employee::GetClassification() const
	{
		return m_classification.get();
	}

	PaymentSchedule* Employee::GetSchedule() const
	{
		return m_schedule.get();
	}

	auto Employee::GetExpenses() const -> Expenses*
	{
		return m_expenses.get();
	}

	void Employee::SetClassification(std::unique_ptr<PaymentClassification> pc)
	{
		m_classification = std::move(pc);
	}

	void Employee::SetSchedule(std::unique_ptr<PaymentSchedule> ps)
	{
		m_schedule = std::move(ps);
	}

	void Employee::SetExpenses(std::unique_ptr<Expenses> a)
	{
		m_expenses = std::move(a);
	}

	bool Employee::IsPayDay(Date d) const
	{
		return m_schedule->IsPayDate(d);
	}

	Paycheck Employee::Payday(Paycheck pc)
	{
		pc.m_grossPay = m_classification->CalculatePay(pc);
		pc.m_deductions = m_expenses->CalculateDeductions(pc);
		pc.m_netPay = pc.m_grossPay - pc.m_deductions;
		return pc;
	}

	Date Employee::GetPayPeriodStartDate(Date d) const
	{
		return m_schedule->GetPayPeriodStartDate(d);
	}

} // namespace Payroll
