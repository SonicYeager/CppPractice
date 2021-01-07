#include "gmock/gmock.h"
#include "../PayrollSystem/PaydayTransaction.h"

class StubEmployee : Payroll::Employee
{
	//TODO
};

class StubDatabase : Payroll::Database
{
public:
	std::vector<int> GetAllEmployeeIds()
	{
		std::vector<int> empl{1,2,3,4,5,6,7,8,9};
		return empl;
	}
};