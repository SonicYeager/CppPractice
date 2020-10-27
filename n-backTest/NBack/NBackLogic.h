#pragma once
#include "Logic.h"

namespace NBACK
{
	class NBACK_API NBackLogic : public Logic
	{
	public:
		void SetData(const TestConfig&) override;
		void RecordStimuli(const bool&) override;
		Lines GetAllTestData() override;
		EvalData EvaluateTest() override;
		void SetStartTime(const std::chrono::system_clock::time_point&) override;
	private:
		EvalData edata{};
	};
}