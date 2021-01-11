#include "HourlyClassification.h"
#include <algorithm>

namespace Payroll
{
	HourlyClassification::HourlyClassification(double rate)
		: m_hourlyRate(rate)
	{}

	void HourlyClassification::AddTimeCard(TimeCard tc)
	{
		auto etc = m_timeCards.find(tc.GetDate());
		if(etc == m_timeCards.end())
			m_timeCards[tc.GetDate()] = tc;
		else
			m_timeCards[tc.GetDate()] = TimeCard(tc.GetDate(), m_timeCards[tc.GetDate()].GetHours() + tc.GetHours());
	}

	TimeCard HourlyClassification::GetTimeCard(Date d)
	{
		return m_timeCards.at(d);
	}

	double HourlyClassification::CalculatePay(const Paycheck& pc)
	{
		double totalPay = 0.0;
		for(const auto& timeCard : m_timeCards)
		{
			if(Date::IsInPeriod(timeCard.first, pc.m_payPeriodStart, pc.m_payPeriodEnd))
				totalPay += CalculatePayForTimeCard(timeCard.second);
		}
		return totalPay;
	}

	double HourlyClassification::CalculatePayForTimeCard(TimeCard card)
	{
		auto overtimeHours = std::max(0.0, card.GetHours() - 8.0);
		auto normalHours = card.GetHours() - overtimeHours;
		return m_hourlyRate * normalHours + m_hourlyRate * 1.5 * overtimeHours;
	}

} // namespace Payroll
