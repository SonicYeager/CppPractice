#include "SalariedClassification.h"

namespace Payroll
{
	SalariedClassification::SalariedClassification(double s)
		: m_salary(s)
	{}

	double SalariedClassification::CalculatePay(const Paycheck&)
	{
		return m_salary;
	}

} // namespace Payroll
