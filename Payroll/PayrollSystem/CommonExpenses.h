#pragma once
#include "Expenses.h"
namespace Payroll
{
	class CommonExpenses : public Expenses
	{
	public:
		double CalculateDeductions(const Paycheck&) override;
	};
} // namespace Payroll
