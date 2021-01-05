#include "PaydayTransaction.h"

namespace Payroll
{
	PaydayTransaction::PaydayTransaction(Paychecks* paychecks, Date payDate, Database* db)
		: m_paychecks(paychecks)
		, m_payDate(payDate)
		, m_database(db)
	{}

	void PaydayTransaction::Execute()
	{
		auto ids = m_database->GetAllEmployeeIds();
		for(int id : ids)
		{
			auto e = m_database->GetEmployee(id);
			if(e->IsPayDay(m_payDate))
			{
				Paycheck pc(e->GetPayPeriodStartDate(m_payDate), m_payDate);
				(*m_paychecks)[id] = e->Payday(pc);
			}
		}
	}
} // namespace Payroll
