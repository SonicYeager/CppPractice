#pragma once
#include "Transaction.h"
#include "Paycheck.h"
#include <map>
#include "PayrollDatabase.h"

namespace Payroll
{
	using Paychecks = std::map<int, Paycheck>;

	class PaydayTransaction : public Transaction
	{
	public:
		PaydayTransaction(Paychecks* paychecks, Date, Database*);

		void Execute() override;

	private:
		Paychecks* m_paychecks;
		Date m_payDate;
		Database* m_database;
	};
} // namespace Payroll
