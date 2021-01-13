#include "BiweeklySchedule.h"

namespace Payroll
{
	Date GetFirstWeeksDateOfYear(Date d)
	{
		if(Date(1,1,d.Year()).GetDayOfWeek() == DayOfWeek::THURSDAY)
		{
			return Date(1, 1, d.Year());
		}
		else
		{
			int days{1};
			while(Date(days, 1, d.Year()).GetDayOfWeek() != DayOfWeek::THURSDAY)
			{
				++days;
			}
			return Date(days - 3, 1, d.Year());
		}
	}

	Date GetMondayDateFromDatesActualWeek(Date d)
	{
		if(d.GetDayOfWeek() == DayOfWeek::MONDAY)
		{
			return d;
		}
		else
		{
			while(d.GetDayOfWeek() != DayOfWeek::MONDAY)
			{
				d = d.AddDays(-1);
			}
			return d;
		}
	}

	int DetermineWeekNoFromDate(Date normalizedDate, Date dateOfFirstWeekInYear)
	{
		int ret{1};

		if(normalizedDate.Year() != dateOfFirstWeekInYear.Year())
		{
			return 53;
		}
		while(not(dateOfFirstWeekInYear == normalizedDate))
		{
			dateOfFirstWeekInYear = dateOfFirstWeekInYear.AddDays(7);
			++ret;
		}

		return ret;
	}

	bool BiweeklySchedule::IsPayDate(Date d) const
	{
		auto normalized = GetMondayDateFromDatesActualWeek(d);
		auto firstWeekDate = GetFirstWeeksDateOfYear({1,1,d.Year()});
		auto weeks = DetermineWeekNoFromDate(normalized, firstWeekDate);
		if((weeks % 2 == 0 || weeks == 53) && d.GetDayOfWeek() == DayOfWeek::FRIDAY)
			return true;
		else
			return false;
	}

	Date ReverseTillDay(Date d, DayOfWeek wd)
	{
		while(d.GetDayOfWeek() != wd)
			d = d.AddDays(-1);
		return d;
	}
	
	Date BiweeklySchedule::GetPayPeriodStartDate(Date d) const
	{
		auto normalized = GetMondayDateFromDatesActualWeek(d);
		auto firstWeekDate = GetFirstWeeksDateOfYear({1, 1, d.Year()});
		auto weeks = DetermineWeekNoFromDate(normalized, firstWeekDate);
		if(weeks == 53)
		{
			if(d.GetDayOfWeek() == DayOfWeek::SATURDARY)
				return d;
			if(d.GetDayOfWeek() == DayOfWeek::SUNDAY)
				return d.AddDays(-1);
			return ReverseTillDay(d, DayOfWeek::SATURDARY);
		}
		if(weeks % 2 == 0)
		{
			if(d.GetDayOfWeek() == DayOfWeek::SATURDARY)
				return d;
			if(d.GetDayOfWeek() == DayOfWeek::SUNDAY)
				return d.AddDays(-1);
			d = ReverseTillDay(d, DayOfWeek::SATURDARY);
			d = d.AddDays(-1);
			d = ReverseTillDay(d, DayOfWeek::SATURDARY);
			return d;
		}
		else
		{
			if(d.GetDayOfWeek() == DayOfWeek::SATURDARY)
				d = d.AddDays(-1);
			return ReverseTillDay(d, DayOfWeek::SATURDARY);
		}
	}
}
