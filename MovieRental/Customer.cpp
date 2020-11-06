#include "Customer.h"
#include <sstream>

Customer::Customer(const std::string& initName)
	: name(initName)
	, rentals{}
{}

Customer::~Customer() {}

void Customer::AddRental(const Rental& r)
{
	rentals.push_back(r);
}

std::string Customer::GetName() const
{
	return name;
}

std::string Customer::Statement() const
{
	double totalAmount{};
	int frequentRenterPoints{};
	for(const Rental& each : rentals)
	{
		double thisAmount = each.CalculateMovieRentCosts();
		totalAmount += thisAmount;
		frequentRenterPoints += each.GetAvailableFrequentRenterPoints();
	}

	std::ostringstream result{};
	result << "Rental Record for " << name << '\n';
	for(const Rental& each : rentals)
	{
		result << '\t' << each.GetMovie().GetTitle() << '\t' << each.CalculateMovieRentCosts() << '\n';
	}
	result << "Amount owed is " << totalAmount << '\n'
		   << "You earned " << frequentRenterPoints << " frequent renter points";
	return result.str();
}
