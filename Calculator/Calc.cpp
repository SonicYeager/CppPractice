#include "Calc.h"

std::stringstream Calc::Add(double numLeft, double numRight) const
{
	std::stringstream res;
	//res << numLeft + numRight;
	return res;
}

std::stringstream Calc::Sub(double numLeft, double numRight) const
{
	std::stringstream res;
	//res << numLeft - numRight;
	return res;
}

std::stringstream Calc::Mul(double numLeft, double numRight) const
{
	std::stringstream res;
	//res << numLeft * numRight;
	return res;
}

std::stringstream Calc::Div(double numLeft, double numRight) const
{
	std::stringstream res;
	//res << numLeft / numRight;
	return res;
}

std::stringstream Calc::Mod(double numLeft, double numRight) const
{
	std::stringstream res;
	//auto divis = static_cast<int>(std::abs(numRight));
	//if(divis == 0)
	//	res << 0.0;
	//else
	//{
	//	auto divid = static_cast<int>(std::abs(numLeft));
	//	if((numLeft < 0 && numRight > 0) || (numLeft > 0 && numRight < 0))
	//		res << -divid % divis;
	//	else
	//		res << divid % divis;
	//}
	return res;
}

std::stringstream Calc::Exp(double numLeft, double numRight) const
{
	std::stringstream res;
	//res << pow(numLeft, numRight);
	return res;
}