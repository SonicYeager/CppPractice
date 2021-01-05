#include "AddSalariedEmployee.h"
#include "MonthlySchedule.h"
#include "SalariedClassification.h"

namespace Payroll
{
	AddSalariedEmployee::AddSalariedEmployee(int empid, const std::string& name, double salary, Database* db)
		: AddEmployeeTransaction(empid, name, db)
		, m_salary(salary)
	{}

	std::unique_ptr<PaymentClassification> AddSalariedEmployee::MakeClassification()
	{
		return std::make_unique<SalariedClassification>(m_salary);
	}

	std::unique_ptr<PaymentSchedule> AddSalariedEmployee::MakeSchedule()
	{
		return std::make_unique<MonthlySchedule>();
	}

} // namespace Payroll
