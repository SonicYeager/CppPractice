#pragma once
#include "ChangeEmployeeTransaction.h"

namespace Payroll
{
	class ChangeGermanExpenses : public ChangeEmployeeTransaction
	{
	public:
		ChangeGermanExpenses(int, Database*);

	protected:
		void Change(Employee*) override;
	};
} // namespace Payroll
