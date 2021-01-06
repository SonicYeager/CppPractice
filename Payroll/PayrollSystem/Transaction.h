#pragma once

namespace Payroll
{
	struct Transaction
	{
		virtual void Execute() = 0;
		virtual ~Transaction() = default;
	};
} // namespace Payroll
