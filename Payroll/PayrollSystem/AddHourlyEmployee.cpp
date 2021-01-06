#include "AddHourlyEmployee.h"
#include "HourlyClassification.h"
#include "WeeklySchedule.h"

namespace Payroll
{
	AddHourlyEmployee::AddHourlyEmployee(int id, const std::string& name, double rate, Database* db)
		: AddEmployeeTransaction(id, name, db)
		, m_hourlyRate(rate)
	{}

	std::unique_ptr<PaymentClassification> AddHourlyEmployee::MakeClassification()
	{
		return std::make_unique<HourlyClassification>(m_hourlyRate);
	}

	std::unique_ptr<PaymentSchedule> AddHourlyEmployee::MakeSchedule()
	{
		return std::make_unique<WeeklySchedule>();
	}

} // namespace Payroll
