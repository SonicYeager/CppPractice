#pragma once
#include "Date.h"

namespace Payroll
{
	class PaymentSchedule
	{
	public:
		virtual bool IsPayDate(Date) const = 0;
		virtual Date GetPayPeriodStartDate(Date) const = 0;

		virtual ~PaymentSchedule() = default;
	};
} // namespace Payroll
