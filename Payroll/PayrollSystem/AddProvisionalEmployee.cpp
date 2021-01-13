#include "AddProvisionalEmployee.h"
#include "BiweeklySchedule.h"
#include "ProvisionClassification.h"

namespace Payroll
{
	AddProvisionalEmployee::AddProvisionalEmployee(int empid, const std::string& name, double salary, double sharesPercentage, Database* db)
		: AddEmployeeTransaction(empid, name, db)
		, m_salary(salary)
		, m_sharesPercentage(sharesPercentage)
	{}

	std::unique_ptr<PaymentClassification>AddProvisionalEmployee::MakeClassification()
	{
		return std::make_unique<ProvisionClassification>(m_salary, m_sharesPercentage);
	}

	std::unique_ptr<PaymentSchedule>AddProvisionalEmployee::MakeSchedule()
	{
		return std::make_unique<BiweeklySchedule>();
	}
}

