#include "GermanExpenses.h"
#include <algorithm>


namespace Payroll
{
	double GermanExpenses::CalculateDeductions(const Paycheck& pc)
	{
		double deduction = pc.m_grossPay * PENSION_INSURENCE;
		deduction += pc.m_grossPay * HEALTH_INSURENCE;
		deduction += CalculateTax(pc.m_grossPay, pc.m_payPeriodStart.Year());
		return deduction;
	}

	double GermanExpenses::CalculateTax(double gross, int year)
	{
		double tax = 0.0;
		if(year < 2005)
		{
			double rest = std::max(gross - 3640, 0.0);
			if(rest > 0)
			{
				double part = std::min(rest, 3640.0);
				tax = part * 0.2;
				rest = std::max(rest - part, 0.0);
			}

			if(rest > 0)
				tax += rest / 2;
		}
		else
		{
			if(gross < 10001)
				tax = 0;
			else
				tax = (gross - 10000) * 5750 / 15000;
		}
		return tax;
	}

} // namespace Payroll
