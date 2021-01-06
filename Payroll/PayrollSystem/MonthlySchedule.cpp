#include "MonthlySchedule.h"

namespace Payroll
{
	bool MonthlySchedule::IsPayDate(Date d) const
	{
		return IsLastDayOfMonth(d);
	}

	Date MonthlySchedule::GetPayPeriodStartDate(Date d) const
	{
		int days = 0;
		while(d.AddDays(days - 1).Month() == d.Month())
			--days;
		return d.AddDays(days);
	}

	bool MonthlySchedule::IsLastDayOfMonth(Date d) const
	{
		auto m1 = d.Month();
		auto m2 = d.AddDays(1).Month();
		return m1 != m2;
	}

} // namespace Payroll
