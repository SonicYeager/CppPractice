#pragma once
#include "Date.h"
#include "Transaction.h"
#include "PayrollDatabase.h"

namespace Payroll
{
	class ReceiptTransaction : public Transaction
	{
	public:
		ReceiptTransaction(Date d, double revenue, int empid, Database* db);

		void Execute() override;

	private:
		Date m_date;
		double m_revenue;
		int m_empid;
		Database* m_database;
	};
} // namespace Payroll
