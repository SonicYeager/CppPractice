#include "ChangeGermanExpenses.h"
#include "GermanExpenses.h"

namespace Payroll
{
	ChangeGermanExpenses::ChangeGermanExpenses(int empid, Database* db)
		: ChangeEmployeeTransaction(empid, db)
	{}

	void ChangeGermanExpenses::Change(Employee* e)
	{
		e->SetExpenses(std::make_unique<GermanExpenses>());
	}
} // namespace Payroll
