#pragma once
#include <string>
#include <memory>
#include "PaymentSchedule.h"
#include "PaymentClassification.h"
#include "Expenses.h"

namespace Payroll
{
	class Employee
	{
	public:
		Employee(int id, const std::string& name);

		auto GetName() const -> std::string;
		auto GetClassification() const -> PaymentClassification*;
		auto GetSchedule() const -> PaymentSchedule*;
		auto GetExpenses() const -> Expenses*;
		void SetClassification(std::unique_ptr<PaymentClassification>);
		void SetSchedule(std::unique_ptr<PaymentSchedule>);
		void SetExpenses(std::unique_ptr<Expenses>);
		bool IsPayDay(Date) const;
		Paycheck Payday(Paycheck);
		Date GetPayPeriodStartDate(Date) const;

	private:
		int m_id;
		std::string m_name;
		std::unique_ptr<PaymentClassification> m_classification = {};
		std::unique_ptr<PaymentSchedule> m_schedule = {};
		std::unique_ptr<Expenses> m_expenses = {};
	};
} // namespace Payroll
