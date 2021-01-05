#pragma once
#include "PaymentSchedule.h"

namespace Payroll
{
	class WeeklySchedule : public PaymentSchedule
	{
	public:
		bool IsPayDate(Date) const override;
		Date GetPayPeriodStartDate(Date) const override;
	};
} // namespace Payroll
