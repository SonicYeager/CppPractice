#pragma once
#include "Paycheck.h"

namespace Payroll
{
	class Expenses
	{
	public:
		virtual double CalculateDeductions(const Paycheck&) = 0;
		virtual ~Expenses() = default;
	};
} // namespace Payroll
