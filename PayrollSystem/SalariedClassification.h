#pragma once
#include "PaymentClassification.h"

namespace Payroll
{
	class SalariedClassification : public PaymentClassification
	{
	public:
		explicit SalariedClassification(double);
		double CalculatePay(const Paycheck&) override;

	private:
		double m_salary;
	};
} // namespace Payroll
