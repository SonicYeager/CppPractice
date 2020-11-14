#pragma once
#include <iostream>
using namespace std;
class Expression
{
public:
	Expression()
	{
		this->value = 0.0;
	}
	Expression(double value)
		: value(value){};
	Expression(const Expression& expression)
		: value(expression.value)
	{}

	virtual double Evaluate()
	{
		return 0.0;
	}
	virtual ostream& Print(ostream& out)
	{
		return out << value;
	}

	virtual ~Expression(){};

	double value;
};

static ostream& operator<<(ostream& os, ostream& sout)
{
	return sout;
}
