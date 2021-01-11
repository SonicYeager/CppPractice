#include "WeeklySchedule.h"


namespace Payroll
{
	bool WeeklySchedule::IsPayDate(Date d) const
	{
		return d.GetDayOfWeek() == DayOfWeek::FRIDAY;
	}

	Date WeeklySchedule::GetPayPeriodStartDate(Date d) const
	{
		while(d.GetDayOfWeek() != DayOfWeek::SATURDARY)
		{
			auto day = d.GetDayOfWeek();
			d = d.AddDays(-1);
		}
		return d;
	}
} // namespace Payroll
