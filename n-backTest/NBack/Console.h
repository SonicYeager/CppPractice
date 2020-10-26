#pragma once
#include "UI.h"

namespace NBACK
{
	class Console : public UI
	{
	public:
		TestData GetUserInput() override;
		bool GetReaction(const std::chrono::milliseconds&, const char&) override;
		void DisplayResults(const EvalData&) override;
	};
}

