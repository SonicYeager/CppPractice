#pragma once
#include "AddEmployeeTransaction.h"

namespace Payroll
{
	class AddHourlyEmployee : public AddEmployeeTransaction
	{
	public:
		explicit AddHourlyEmployee(int id, const std::string& name, double rate, Database*);

	protected:
		std::unique_ptr<PaymentClassification> MakeClassification() override;
		std::unique_ptr<PaymentSchedule> MakeSchedule() override;

	private:
		double m_hourlyRate;
	};
} // namespace Payroll
