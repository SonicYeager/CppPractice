#pragma once
#include <string>

enum class DayOfWeek
{
	SUNDAY = 0,
	MONDAY,
	THUESDAY,
	WEDNESDAY,
	THURSDAY,
	FRIDAY,
	SATURDARY
};

class Date
{
public:
	Date() = default;
	Date(int d, int m, int y);
	auto Year() const -> int;
	auto Month() const -> int;
	auto Day() const -> int;

	auto AddDays(int days) const -> Date;
	auto GetDayOfWeek() const -> DayOfWeek;

	static auto IsInPeriod(Date c, Date min, Date max) -> bool;
	static auto DiffDays(Date start, Date end) -> int;
	static auto FromString(const std::string&) -> Date;
	static auto ToString(Date) -> std::string;

private:
	int m_day = 1;
	int m_month = 1;
	int m_year = 1900;
};

bool operator<(const Date&, const Date&);
bool operator==(const Date&, const Date&);
