#include "Date.h"
#include <sstream>
#include <vector>

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

std::vector<int> GetDaysPerMonth(int year)
{
	std::vector<int> daysPerMonth = {0, 31, 29, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
	if(year % 4 == 0 && year % 100 == 0 && year % 400 == 0)
	{
		daysPerMonth[1] = 28;
		return daysPerMonth;
	}
	else
		return daysPerMonth;
}

int GetPreviousMonth(int actualMonth)
{
	if(actualMonth == 12)
		return 1;
	if (actualMonth == 1)
		return 12;
	return --actualMonth;
}

auto Date::AddDays(int days) const -> Date //room for more days is not yet present (minus or plus 62 days will never work correctly)
{
	const std::vector<int> daysPerMonth = GetDaysPerMonth(m_year);
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
		newDays = daysPerMonth[GetPreviousMonth(m_month)] + newDays;
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
	auto d = m_day;
	auto m = m_month;
	auto y = m_year;

	if (m < 3)
		y = y - 1;
	double w = std::fmod((std::fmod((d + std::floor(2.6 * ((m + 9) % 12 + 1) - 0.2) + y % 100 + std::floor(y % 100 / 4) + std::floor(y / 400) - 2 * std::floor(y / 100) - 1), 7) + 7), 7) + 1;
	return DayOfWeek(w == 7 ? 0 : w);
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
	const std::vector<int> startDaysPerMonth = GetDaysPerMonth(start.m_year);
	const std::vector<int> endDaysPerMonth = GetDaysPerMonth(end.m_year);
	const int numMonths = end.m_month - start.m_month;
	if(numMonths == 0)
		return std::abs(end.m_day - start.m_day);
	else if(numMonths > 0)
		return startDaysPerMonth[start.m_month] - start.m_day + end.m_day;
	else
		return endDaysPerMonth[end.m_month] - end.m_day + start.m_day;
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

