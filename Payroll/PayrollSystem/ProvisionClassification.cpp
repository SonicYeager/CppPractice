#include "ProvisionClassification.h"

namespace Payroll
{
	ProvisionClassification::ProvisionClassification(double sharesPercentage, double salary)
		: m_salary(salary)
		, m_sharesPercentage(sharesPercentage)
	{}
	
	double ProvisionClassification::CalculatePay(const Paycheck& pc)
	{
		double totalPay = 0.0;
		for(const auto& receipt : m_receipts)
		{
			if(Date::IsInPeriod(receipt.first, pc.m_payPeriodStart, pc.m_payPeriodEnd))
				totalPay += CalculatePayForTimeCard(receipt.second);
		}
		return totalPay + m_salary;
	}
	
	void ProvisionClassification::AddReceipt(Receipt r)
	{
		auto etc = m_receipts.find(r.GetDate());
		if(etc == m_receipts.end())
			m_receipts[r.GetDate()] = r;
		else
			m_receipts[r.GetDate()] = Receipt(r.GetDate(), m_receipts[r.GetDate()].GetRevenue() + r.GetRevenue());
	}
	
	Receipt ProvisionClassification::GetReceipt(Date d)
	{
		return m_receipts.at(d);
	}
	
	double ProvisionClassification::CalculatePayForTimeCard(Receipt receipt)
	{
		return receipt.GetRevenue() * m_sharesPercentage;
	}
}
