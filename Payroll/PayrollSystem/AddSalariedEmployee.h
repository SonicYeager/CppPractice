#pragma once
#include "AddEmployeeTransaction.h"

namespace Payroll
{
	class AddSalariedEmployee : public AddEmployeeTransaction
	{
	public:
		AddSalariedEmployee(int empid, const std::string& name, double salary, Database* db);

	protected:
		std::unique_ptr<PaymentClassification> MakeClassification() override;
		std::unique_ptr<PaymentSchedule> MakeSchedule() override;

	private:
		double m_salary = 0.0;
	};
} // namespace Payroll
