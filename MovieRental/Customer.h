#pragma once

#include "Rental.h"
#include <string>
#include <vector>

class Customer
{
public:
	explicit Customer(const std::string& initName);
	~Customer();

	void AddRental(const Rental&);
	std::string GetName() const;
	std::string Statement() const;
	std::vector<Rental> GetRentals() const;

private:
	std::string name;
	std::vector<Rental> rentals;

};
