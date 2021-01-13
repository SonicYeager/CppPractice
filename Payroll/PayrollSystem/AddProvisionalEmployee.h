#pragma once
#include "AddEmployeeTransaction.h"

namespace Payroll
{
	class AddProvisionalEmployee : public AddEmployeeTransaction
	{
	public:
		AddProvisionalEmployee(int empid, const std::string& name, double salary, double sharesPercentage, Database* db);

	protected:
		std::unique_ptr<PaymentClassification> MakeClassification() override;
		std::unique_ptr<PaymentSchedule> MakeSchedule() override;

	private:
		double m_salary = 0.0;
		double m_sharesPercentage = 0.0;
	};
}