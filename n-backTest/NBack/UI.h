#pragma once
#include "InternalTypes.h"

namespace NBACK
{
	class NBACK_API UI
	{
	public:
		virtual TestData GetUserInput() = 0;
		virtual bool GetReaction(const std::chrono::milliseconds&, const char&) = 0;
		virtual void DisplayResults(const EvalData&) = 0;
		virtual ~UI() = default;
	};
}
