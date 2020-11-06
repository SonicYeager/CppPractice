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

double Rental::CalculateMovieRentCosts() const
{
	double res{};
	switch(movie.GetPriceCode())
	{
		case Movie::REGULAR: {
			res += 2;
			if(GetDaysRent() > 2)
				res += ((double)GetDaysRent() - 2) * 1.5;
			break;
		}
		case Movie::NEW_RELEASE: {
			res += (double)GetDaysRent() * 3;
			break;
		}
		case Movie::CHILDRENS: {
			res += 1.5;
			if(GetDaysRent() > 3)
				res += ((double)GetDaysRent() - 3) * 1.5;
			break;
		}
	}
	return res;
}

int Rental::GetAvailableFrequentRenterPoints() const
{
	int points{};
	if((movie.GetPriceCode() == Movie::NEW_RELEASE) && (GetDaysRent() > 1))
		++points;
	++points;
	return points;
}
