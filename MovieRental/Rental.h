#pragma once

#include "Movie.h"

class Rental
{
public:
	Rental(const Movie& initMovie, int initDaysRent);
	~Rental();

	int GetDaysRent() const;
	const Movie& GetMovie() const;

private:
	Movie movie;
	int daysRent;
};
