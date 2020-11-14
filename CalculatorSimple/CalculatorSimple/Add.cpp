#include "Add.h"


Add::Add(Expression* leftExpression, Expression* rightExpression)
	: expressionLeft(leftExpression)
	, expressionRight(rightExpression)
{
	this->value = Evaluate();
}

double Add::Evaluate()
{
	return expressionLeft->value + expressionRight->value;
}

ostream& Add::Print(ostream& out)
{
	return expressionLeft->Print(out) << " + " << expressionRight->Print(out) << ' ';
}

Add::~Add()
{
	delete expressionLeft;
	delete expressionRight;
}
