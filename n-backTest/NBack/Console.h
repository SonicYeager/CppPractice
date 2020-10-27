#pragma once
#include "UI.h"

namespace NBACK
{
	class Console : public UI
	{
	public:
		TestData GetUserInput() override;
		REACTION GetReaction(const std::chrono::milliseconds&, const char&) override;
		bool DisplayYesNoQuestion(const std::string&) override;
		void DisplayResults(const EvalData&) override;
	};
}

