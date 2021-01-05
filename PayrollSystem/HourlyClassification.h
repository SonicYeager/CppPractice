#pragma once
#include "PaymentClassification.h"
#include <map>
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
