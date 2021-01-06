#include "TimeCard.h"

namespace Payroll
{
	TimeCard::TimeCard(Date d, double h)
		: m_date(d)
		, m_hours(h)
	{}

	double TimeCard::GetHours() const
	{
		return m_hours;
	}

	Date TimeCard::GetDate() const
	{
		return m_date;
	}
} // namespace Payroll
