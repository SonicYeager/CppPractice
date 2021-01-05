#include "PayrollDatabase.h"

namespace Payroll
{
	void Database::AddEmployee(int id, std::unique_ptr<Employee> e)
	{
		m_items[id] = std::move(e);
	}

	Employee* Database::GetEmployee(int id)
	{
		return m_items[id].get();
	}

	std::vector<int> Database::GetAllEmployeeIds()
	{
		std::vector<int> result;
		for(auto& item : m_items)
			result.push_back(item.first);
		return result;
	}
} // namespace Payroll
