#pragma once
#include "Date.h"
#include "Transaction.h"
#include "PayrollDatabase.h"

namespace Payroll
{
	class TimeCardTransaction : public Transaction
	{
	public:
		TimeCardTransaction(Date d, double h, int empid, Database* db);

		void Execute() override;

	private:
		Date m_date;
		double m_hours;
		int m_empid;
		Database* m_database;
	};
} // namespace Payroll
