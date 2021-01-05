#pragma once
#include "Expenses.h"

namespace Payroll
{
	class GermanExpenses : public Expenses
	{
	public:
		double CalculateDeductions(const Paycheck&) override;

	private:
		double CalculateTax(double gross, int year);
		const double PENSION_INSURENCE = 0.186;
		const double HEALTH_INSURENCE = 0.146;
	};
} // namespace Payroll
