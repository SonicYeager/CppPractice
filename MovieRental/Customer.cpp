#include "Customer.h"
#include <sstream>

Customer::Customer(const std::string& initName)
	: name(initName)
	, rentals{}
{}

Customer::~Customer() {}

void Customer::AddRental(const Rental& r)
{
	this->rentals.push_back(r);
}

std::string Customer::GetName() const
{
	return this->name;
}

std::string Customer::Statement() const
{
	double totalAmount = 0.0;
	int frequentRenterPoints = 0;
	std::ostringstream result;
	result << "Rental Record for " << this->name << '\n'; //head

	//body
	for(const Rental& each : this->rentals)
	{
		double thisAmount = each.CalculateMovieRentCosts();

		if((each.GetMovie().GetPriceCode() == Movie::NEW_RELEASE) && (each.GetDaysRent() > 1))
			++frequentRenterPoints;
		++frequentRenterPoints;

		result << '\t' << each.GetMovie().GetTitle() << '\t' << thisAmount << '\n';
		totalAmount += thisAmount;
	}

	result << "Amount owed is " << totalAmount << '\n'
		   << "You earned " << frequentRenterPoints << " frequent renter points"; //footer
	return result.str();
}
