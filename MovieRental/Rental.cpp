#include "Rental.h"

Rental::Rental(const Movie& initMovie, int initDaysRent)
	: movie(initMovie)
	, daysRent(initDaysRent)
{}
Rental::~Rental() {}

int Rental::GetDaysRent() const
{
	return this->daysRent;
}

const Movie& Rental::GetMovie() const
{
	return this->movie;
}
