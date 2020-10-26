#pragma once
#include "InternalTypes.h"

namespace NBACK
{
	class NBACK_API Logic
	{
	public:
		virtual void RecordStimuli(const bool&) = 0;
		virtual Lines GetAllTestData() = 0;
		virtual EvalData EvaluateTest() = 0;
		virtual void SetStartTime(const std::chrono::system_clock::time_point&) = 0;
		virtual ~Logic() = default;
	};
}