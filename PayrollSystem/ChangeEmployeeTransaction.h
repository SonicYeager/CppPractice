#pragma once
#include "Transaction.h"
#include "PayrollDatabase.h"

namespace Payroll
{
	class ChangeEmployeeTransaction : public Transaction
	{
	public:
		ChangeEmployeeTransaction(int, Database*);
		void Execute() override;

	protected:
		virtual void Change(Employee*) = 0;

	private:
		int m_empid;
		Database* m_database;
	};
} // namespace Payroll
