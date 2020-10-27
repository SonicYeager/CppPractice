#pragma once
#include "UI.h"

namespace NBACK
{
	class NBACK_API Console : public UI
	{
	public:
		TestConfig GetUserInput() const override;
		std::future<void> DisplayStimuli(char, int, const std::chrono::milliseconds&) override;
		void GetReaction(const std::chrono::milliseconds&, Event, Event, Event) const override;
		void Countdown(int) const override;
		void DisplayResults(const EvalData&) const override;
	};
}

