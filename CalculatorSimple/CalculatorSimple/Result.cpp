#include "Result.h"

Result::Result(Expression* expression)
	: expression(expression)
{
	value = this->expression->Evaluate();
}

Result::~Result()
{
	delete expression;
}

double Result::Evaluate()
{
	return expression->Evaluate();
}

ostream& Result::Print(ostream& out)
{
	return expression->Print(out);
}

void Result::operator=(Expression* expression)
{
	this->expression = expression;
}
