#pragma once
#include "Date.h"


namespace Payroll
{
	class TimeCard
	{
	public:
		TimeCard() = default;
		TimeCard(Date, double);

		double GetHours() const;
		Date GetDate() const;

	private:
		Date m_date = {};
		double m_hours = 50.0;
	};

} // namespace Payroll
