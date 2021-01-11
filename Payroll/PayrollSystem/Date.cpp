#include "Date.h"
#include <sstream>

Date::Date(int d, int m, int y)
	: m_day(d)
	, m_month(m)
	, m_year(y)
{}

auto Date::Year() const -> int
{
	return m_year;
}

auto Date::Month() const -> int
{
	return m_month;
}

auto Date::Day() const -> int
{
	return m_day;
}

auto Date::AddDays(int days) const -> Date
{
	const int daysPerMonth[] = {31, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
	auto newDays = m_day + days;
	auto newMonth = m_month;
	auto newYear = m_year;
	if(newDays > daysPerMonth[m_month])
	{
		newDays -= daysPerMonth[m_month];
		newMonth += 1;
		if(newMonth > 12)
		{
			newMonth = 1;
			++newYear;
		}
	}
	else if(newDays <= 0)
	{
		newDays = daysPerMonth[m_month - 1] + newDays;
		newMonth -= 1;
		if(newMonth < 1)
		{
			newMonth = 12;
			--newYear;
		}
	}
	return Date(newDays, newMonth, newYear);
}

auto Date::GetDayOfWeek() const -> DayOfWeek
{
	return DayOfWeek((m_day - 3) % 7);
}

auto Date::IsInPeriod(Date c, Date min, Date max) -> bool
{
	return not(max < c or c < min);
}

auto Date::FromString(const std::string& text) -> Date
{
	Date date;
	std::istringstream ss(text);
	ss >> date.m_day >> date.m_month >> date.m_year;
	return date;
}

auto Date::ToString(Date d) -> std::string
{
	std::string result(std::to_string(d.m_year));
	result.push_back('.');
	result.append(std::to_string(d.m_month));
	result.push_back('.');
	result.append(std::to_string(d.m_day));
	return result;
}

auto Date::DiffDays(Date start, Date end) -> int
{
	const int daysPerMonth[] = {31, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
	const int numMonths = end.m_month - start.m_month;
	if(numMonths == 0)
		return std::abs(end.m_day - start.m_day);
	else if(numMonths > 0)
		return daysPerMonth[start.m_month] - start.m_day + end.m_day;
	else
		return daysPerMonth[end.m_month] - end.m_day + start.m_day;
}

bool operator<(const Date& left, const Date& right)
{
	if(left.Year() < right.Year())
		return true;
	else if(left.Year() == right.Year())
	{
		if(left.Month() < right.Month())
			return true;
		else if(left.Month() == right.Month() and left.Day() < right.Day())
			return true;
	}
	return false;
}

bool operator==(const Date& left, const Date& right)
{
	return left.Day() == right.Day() and left.Month() == right.Month() and left.Year() == right.Year();
}

