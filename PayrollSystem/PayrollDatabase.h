#pragma once
#include "Employee.h"
#include <map>
#include <vector>

namespace Payroll
{
	class Database
	{
	public:
		void AddEmployee(int id, std::unique_ptr<Employee>);
		Employee* GetEmployee(int id);
		std::vector<int> GetAllEmployeeIds();

	private:
		std::map<int, std::unique_ptr<Employee>> m_items = {};
	};
} // namespace Payroll
