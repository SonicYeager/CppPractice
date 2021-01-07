#include "gmock/gmock.h"
#include "../PayrollSystem/Date.h"

std::ostream& operator<< (std::ostream& os, const Date& date)
{
	return os << date.Day() << " | " << date.Month() << " | " << date.Year();
}

std::ostream& operator<< (std::ostream& os, const DayOfWeek& date)
{
	switch (date)
	{
	case DayOfWeek::MONDAY:
		return os << "MONDAY";
	case DayOfWeek::THUESDAY:
		return os << "THUESDAY";
	case DayOfWeek::WEDNESDAY:
		return os << "WEDNESDAY";
	case DayOfWeek::THURSDAY:
		return os << "THURSDAY";
	case DayOfWeek::FRIDAY:
		return os << "FRIDAY";
	case DayOfWeek::SATURDARY:
		return os << "SATURDARY";
	case DayOfWeek::SUNDAY:
		return os << "SUNDAY";
	}
}

TEST(TestDate, AddDays_Five_ReturnSithOfFirst)
{
	Date d{1,1,2021};
	
	auto actual = d.AddDays(5);

	Date expected{6,1,2021};
	EXPECT_EQ(actual, expected);
}

TEST(TestDate, AddDays_MinusFive_ReturnFirstOfFirst)
{
	Date d{ 6,1,2021 };

	auto actual = d.AddDays(-5);

	Date expected{ 1,1,2021 };
	EXPECT_EQ(actual, expected);
}

TEST(TestDate, AddDays_One_ReturnFirstOfNextMonth)
{
	Date d{ 31,1,2021 };

	auto actual = d.AddDays(1);

	Date expected{ 1,2,2021 };
	EXPECT_EQ(actual, expected);
}

TEST(TestDate, AddDays_MinusOne_ReturnLastOfPreviousMonth)
{
	Date d{ 1,2,2021 };

	auto actual = d.AddDays(-1);

	Date expected{ 31,1,2021 };
	EXPECT_EQ(actual, expected);
}

TEST(TestDate, AddDays_One_ReturnFirstOfNextMonthAndYear)
{
	Date d{ 31,12,2020 };

	auto actual = d.AddDays(1);

	Date expected{ 1,1,2021 };
	EXPECT_EQ(actual, expected);
}

TEST(TestDate, AddDays_MinusOne_ReturnLastOfPreviousMonthAndYear)
{
	Date d{ 1,1,2021 };

	auto actual = d.AddDays(-1);

	Date expected{ 31,12,2020 };
	EXPECT_EQ(actual, expected);
}

TEST(TestDate, AddDays_One_ReturnTwentynine)
{
	Date d{ 28,2,2020 };

	auto actual = d.AddDays(1);

	Date expected{ 29,2,2020 };
	EXPECT_EQ(actual, expected);
}

TEST(TestDate, GetDayOfWeek_Mon_ReturnMon)
{
	Date d{ 4,1,2021 };

	auto actual = d.GetDayOfWeek();
	EXPECT_EQ(actual, DayOfWeek::MONDAY);
}

TEST(TestDate, GetDayOfWeek_Tue_ReturnTue)
{
	Date d{ 5,1,2021 };

	auto actual = d.GetDayOfWeek();
	EXPECT_EQ(actual, DayOfWeek::THUESDAY);
}
TEST(TestDate, GetDayOfWeek_Wed_ReturnWed)
{
	Date d{ 6,1,2021 };

	auto actual = d.GetDayOfWeek();
	EXPECT_EQ(actual, DayOfWeek::WEDNESDAY);
}
TEST(TestDate, GetDayOfWeek_Thu_ReturnThu)
{
	Date d{ 7,1,2021 };

	auto actual = d.GetDayOfWeek();
	EXPECT_EQ(actual, DayOfWeek::THURSDAY);
}
TEST(TestDate, GetDayOfWeek_Fri_ReturnFri)
{
	Date d{ 8,1,2021 };

	auto actual = d.GetDayOfWeek();
	EXPECT_EQ(actual, DayOfWeek::FRIDAY);
}
TEST(TestDate, GetDayOfWeek_Sat_ReturnSat)
{
	Date d{ 9,1,2021 };

	auto actual = d.GetDayOfWeek();
	EXPECT_EQ(actual, DayOfWeek::SATURDARY);
}

TEST(TestDate, GetDayOfWeek_Sun_ReturnSun)
{
	Date d{ 10,1,2021 };

	auto actual = d.GetDayOfWeek();
	EXPECT_EQ(actual, DayOfWeek::SUNDAY);
}