#pragma once
#include "cards.h"
#include "internaltypes.h"

struct CardStack
{
	void LoadStack();
	std::vector<Card> DrawCards(int);
	Card DrawCard();
	void MixCards();

private:
	std::vector<Card> stack{};
};