#include "AddEmployeeTransaction.h"
#include "PayrollDatabase.h"

namespace Payroll
{
	AddEmployeeTransaction::AddEmployeeTransaction(int empid, const std::string& name, Database* db)
		: m_empid(empid)
		, m_name(name)
		, m_database(db)
	{}

	void AddEmployeeTransaction::Execute()
	{
		auto pc = MakeClassification();
		auto ps = MakeSchedule();

		auto e = std::make_unique<Employee>(m_empid, m_name);
		e->SetClassification(std::move(pc));
		e->SetSchedule(std::move(ps));

		m_database->AddEmployee(m_empid, std::move(e));
	}
} // namespace Payroll
