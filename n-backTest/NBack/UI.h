#pragma once
#include "InternalTypes.h"

namespace NBACK
{
	class NBACK_API UI
	{
	public:
		virtual TestConfig GetUserInput() const = 0;
		virtual void DisplayStimuli(char, int, const std::chrono::milliseconds&) = 0;
		virtual void GetReaction(Event, Event, Event) const = 0;
		virtual void DisplayResults(const EvalData&) const = 0;
		virtual void Countdown(int) const = 0;
		virtual ~UI() = default;
	};
}
