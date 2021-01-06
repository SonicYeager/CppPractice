#pragma once
#include "Date.h"

namespace Payroll
{
	struct Paycheck
	{
		Paycheck() = default;
		Paycheck(Date, Date);
		Date m_payPeriodStart = {};
		Date m_payPeriodEnd = {};
		double m_grossPay = 0.0;
		double m_netPay = 0.0;
		double m_deductions = 0.0;
	};

	inline Paycheck::Paycheck(Date s, Date e)
		: m_payPeriodStart(s)
		, m_payPeriodEnd(e)
	{}

} // namespace Payroll
