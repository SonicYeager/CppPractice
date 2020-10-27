#pragma once
#include "UI.h"

namespace NBACK
{
	class NBACK_API Console : public UI
	{
	public:
		TestConfig GetUserInput() const override;
		void DisplayStimuli(char) const override;
		REACTION GetReaction(const std::chrono::milliseconds&) const override;
		void Countdown(int) const override;
		void DisplayResults(const EvalData&) const override;
	};
}

