#include "ChangeEmployeeTransaction.h"


namespace Payroll
{
	ChangeEmployeeTransaction::ChangeEmployeeTransaction(int empid, Database* db)
		: m_empid(empid)
		, m_database(db)
	{}

	void ChangeEmployeeTransaction::Execute()
	{
		auto e = m_database->GetEmployee(m_empid);
		if(e)
			Change(e);
	}
} // namespace Payroll
