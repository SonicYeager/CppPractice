#pragma once
#include <map>
#include "PaymentClassification.h"
#include "TimeCard.h"

namespace Payroll
{
	class HourlyClassification : public PaymentClassification
	{
	public:
		explicit HourlyClassification(double rate);

		double CalculatePay(const Paycheck&) override;

		void AddTimeCard(TimeCard);
		TimeCard GetTimeCard(Date);

	private:
		double CalculatePayForTimeCard(TimeCard second);
		double m_hourlyRate;
		std::map<Date, TimeCard> m_timeCards = {};
	};

} // namespace Payroll
