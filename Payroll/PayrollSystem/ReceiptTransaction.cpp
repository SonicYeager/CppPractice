#include "ReceiptTransaction.h"
#include "ProvisionClassification.h"

Payroll::ReceiptTransaction::ReceiptTransaction(Date d, double revenue, int empid, Database* db)
	: m_date(d)
	, m_revenue(revenue)
	, m_empid(empid)
	, m_database(db)
{}

void Payroll::ReceiptTransaction::Execute()
{
	auto e = m_database->GetEmployee(m_empid);
	if(e != nullptr)
	{
		auto hc = dynamic_cast<ProvisionClassification*>(e->GetClassification());
		if(hc != nullptr)
			hc->AddReceipt(Receipt(m_date, m_revenue));
	}
}
