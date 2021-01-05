#pragma once
#include "Transaction.h"
#include <string>
#include "PayrollDatabase.h"

namespace Payroll
{
	class PaymentClassification;
	class PaymentSchedule;

	class AddEmployeeTransaction : public Transaction
	{
	public:
		AddEmployeeTransaction(int empid, const std::string& name, Database* db);
		void Execute() override;

	protected:
		virtual std::unique_ptr<PaymentClassification> MakeClassification() = 0;
		virtual std::unique_ptr<PaymentSchedule> MakeSchedule() = 0;

	private:
		int m_empid;
		std::string m_name;
		Database* m_database;
	};
} // namespace Payroll
