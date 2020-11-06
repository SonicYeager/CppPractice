#pragma once

#include <string>

class Movie
{
public:
	enum
	{
		CHILDRENS = 2,
		REGULAR = 0,
		NEW_RELEASE = 1
	};

	Movie(const std::string& initTitle, int initPriceCode);
	~Movie();

	int GetPriceCode() const;
	void SetPriceCode(int newPriceCode);
	std::string GetTitle() const;

private:
	std::string title;
	int priceCode;
};
