#pragma once
#include "cards.h"
#include <vector>

struct CardStack
{
	void LoadStack();
private:
	std::vector<Card> stack{};
};