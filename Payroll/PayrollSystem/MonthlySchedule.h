#pragma once
#include "PaymentSchedule.h"

namespace Payroll
{
	class MonthlySchedule : public PaymentSchedule
	{
	public:
		bool IsPayDate(Date) const override;
		Date GetPayPeriodStartDate(Date) const override;

	private:
		bool IsLastDayOfMonth(Date) const;
	};
} // namespace Payroll
