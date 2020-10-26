#pragma once
#include "Logic.h"

namespace NBACK
{
	class NBACK_API NBackLogic : public Logic
	{
	public:
		NBackLogic(const TestData&);
		void RecordStimuli(const bool&) override;
		Lines GetAllTestData() override;
		EvalData EvaluateTest() override;
		void SetStartTime(const std::chrono::system_clock::time_point&) override;
	private:
		TestData tdata{};
		EvalData edata{};
	};
}