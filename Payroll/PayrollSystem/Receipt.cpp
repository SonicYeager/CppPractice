#include "Receipt.h"

Payroll::Receipt::Receipt(Date d, double rev) 
	: m_date(d)
	, m_revenue(rev)
{}

double Payroll::Receipt::GetRevenue() const
{
	return m_revenue;
}

Date Payroll::Receipt::GetDate() const
{
	return m_date;
}
