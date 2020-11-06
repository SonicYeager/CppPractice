#include "Movie.h"

Movie::Movie(const std::string& initTitle, int initPriceCode)
	: title(initTitle)
	, priceCode(initPriceCode)
{}

Movie::~Movie() {}

int Movie::GetPriceCode() const
{
	return this->priceCode;
}

void Movie::SetPriceCode(int newPriceCode)
{
	this->priceCode = newPriceCode;
}

std::string Movie::GetTitle() const
{
	return this->title;
}
