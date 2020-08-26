#include "Clip.h"

Clip::Clip(std::chrono::milliseconds s, std::chrono::milliseconds len)
	: number(NextNumber())
	, start(s)
	, length(len)
{}

int Clip::NextNumber()
{
	static int number = 1;
	return number++;
}
