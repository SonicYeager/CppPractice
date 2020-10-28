#pragma once
#include "Logic.h"

namespace NBACK
{
	class NBACK_API NBackLogic : public Logic
	{
	public:
		void SetData(const TestConfig&) override;
		void SetUpdateInterval(const std::chrono::milliseconds&);
		void RecordStimuli(const bool&) override;
		Lines GetAllTestData() override;
		EvalData EvaluateTest() override;
		void UpdateDisplay(std::function<void(char, int, const std::chrono::milliseconds&)>, char) override;
		void SetStartTime(const std::chrono::system_clock::time_point&) override;
	private:
		EvalData edata{};
		int presented{};
		std::chrono::milliseconds interval{100ms};
	};
}