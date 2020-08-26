#pragma once
#include "IVisitor.h"
#include <chrono>

using namespace std::chrono_literals;

class Clip : public IVisitable
{
public:
	Clip(std::chrono::milliseconds start, std::chrono::milliseconds length);
	int number;
	std::chrono::milliseconds start;
	std::chrono::milliseconds length;

	static int NextNumber();
	virtual ~Clip() = default;
};
