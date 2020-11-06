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
	result << "Rental Record for " << this->name << '\n';
	for(const Rental& each : this->rentals)
	{
		double thisAmount = 0.0;
		// determine amount for each line
		switch(each.GetMovie().GetPriceCode())
		{
		case Movie::REGULAR:
		{
			thisAmount += 2;
			if(each.GetDaysRent() > 2)
				thisAmount += (each.GetDaysRent() - 2) * 1.5;
			break;
		}
		case Movie::NEW_RELEASE:
		{
			thisAmount += each.GetDaysRent() * 3;
			break;
		}
		case Movie::CHILDRENS:
		{
			thisAmount += 1.5;
			if(each.GetDaysRent() > 3)
				thisAmount += (each.GetDaysRent() - 3) * 1.5;
			break;
		}
		}
		// add frequent renter points
		++frequentRenterPoints;
		// add bonus for a two day new release rental
		if((each.GetMovie().GetPriceCode() == Movie::NEW_RELEASE) && (each.GetDaysRent() > 1))
			++frequentRenterPoints;

		// show figures for this rental
		result << '\t' << each.GetMovie().GetTitle() << '\t' << thisAmount << '\n';
		totalAmount += thisAmount;
	}

	// add footer
	result << "Amount owed is " << totalAmount << '\n'
		   << "You earned " << frequentRenterPoints << " frequent renter points";
	return result.str();
}
