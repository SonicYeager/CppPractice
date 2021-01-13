#include "BiweeklySchedule.h"

namespace Payroll
{
	bool BiweeklySchedule::IsPayDate(Date) const
	{
		return false; //TODO
	}
	
	Date BiweeklySchedule::GetPayPeriodStartDate(Date) const
	{
		return Date(); //TODO
	
	}
}
