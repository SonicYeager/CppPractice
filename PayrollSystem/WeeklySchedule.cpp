#include "WeeklySchedule.h"


namespace Payroll
{
	bool WeeklySchedule::IsPayDate(Date d) const
	{
		return d.GetDayOfWeek() == DayOfWeek::FRIDAY;
	}

	Date WeeklySchedule::GetPayPeriodStartDate(Date d) const
	{
		return d.AddDays(-6);
	}
} // namespace Payroll
