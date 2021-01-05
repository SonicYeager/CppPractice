#include "TimeCardTransaction.h"
#include "TimeCard.h"
#include "HourlyClassification.h"

namespace Payroll
{
	TimeCardTransaction::TimeCardTransaction(Date d, double h, int empid, Database* db)
		: m_date(d)
		, m_hours(h)
		, m_empid(empid)
		, m_database(db)
	{}

	void TimeCardTransaction::Execute()
	{
		auto e = m_database->GetEmployee(m_empid);
		if(e != nullptr)
		{
			auto hc = dynamic_cast<HourlyClassification*>(e->GetClassification());
			if(hc != nullptr)
				hc->AddTimeCard(TimeCard(m_date, m_hours));
		}
	}

} // namespace Payroll
