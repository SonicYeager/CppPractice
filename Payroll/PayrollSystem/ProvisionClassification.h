#pragma once
#include "PaymentClassification.h"
#include "Receipt.h"
#include <map>

namespace Payroll
{
	class ProvisionClassification : public PaymentClassification
	{
	public:
		explicit ProvisionClassification(double sharesPercentage, double salary);

		double CalculatePay(const Paycheck&) override;

		void AddReceipt(Receipt);
		Receipt GetReceipt(Date);

	private:
		double CalculatePayForTimeCard(Receipt second);
		double m_sharesPercentage;
		double m_salary;
		std::map<Date, Receipt> m_receipts = {};
	};
}