#pragma once
#include "UI.h"

namespace NBACK
{
	class Console : public UI
	{
	public:
		virtual TestData GetUserInput() = 0;
		virtual bool GetReaction(const std::chrono::milliseconds&, const char&) = 0;
		virtual void DisplayResults(const EvalData&) = 0;
	};
}

