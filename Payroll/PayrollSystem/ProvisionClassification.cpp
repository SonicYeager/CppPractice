#include "ProvisionClassification.h"

namespace Payroll
{
	ProvisionClassification::ProvisionClassification(double sharesPercentage, double salary)
		: m_salary(salary)
		, m_sharesPercentage(sharesPercentage)
	{}
	
	double ProvisionClassification::CalculatePay(const Paycheck&)
	{
		return 0.0;	//TODO
	}
	
	void ProvisionClassification::AddReceipt(Receipt)
	{
		//TODO
	}
	
	Receipt ProvisionClassification::GetReceipt(Date d)
	{
		return m_receipts.at(d);
	}
	
	double ProvisionClassification::CalculatePayForTimeCard(Receipt second)
	{
		return 0.0;	//TODO
	
	}
}
