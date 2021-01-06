#include "CommonExpenses.h"


double Payroll::CommonExpenses::CalculateDeductions(const Paycheck& pc)
{
	return pc.m_grossPay * 0.3;
}
