#pragma once
#include "Paycheck.h"

namespace Payroll
{
	class PaymentClassification
	{
	public:
		virtual double CalculatePay(const Paycheck&) = 0;
		virtual ~PaymentClassification() = default;
	};
} // namespace Payroll
