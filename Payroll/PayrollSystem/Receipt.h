#pragma once
#include "Date.h"

namespace Payroll
{
	class Receipt
	{
	public:
		Receipt() = default;
		Receipt(Date, double);

		double GetRevenue() const;
		Date GetDate() const;

	private:
		Date m_date = {};
		double m_revenue = 0.0;
	};

} // namespace Payroll