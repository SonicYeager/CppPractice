#include "pch.h"
#include <iostream>

struct Complex {
	float re = 0;
	float im = 0;
};

float AbsoluteValue(Complex num) {
	float res;
	return res = sqrt(pow(num.re, 2) + pow(num.im, 2)); //alternativ liese sich auch ein annäherungs algo für wurzelziehen aufsetzen
}

Complex ComplexConjugate(Complex num) {
	return { num.re, -num.im };
}

Complex Add(Complex numA, Complex numB) {
	Complex res;
	res.re = numA.re + numB.re;
	res.im = numA.im + numB.im;
	return res;
}

Complex Sub(Complex numA, Complex numB) {
	Complex res;
	res.re = numA.re - numB.re;
	res.im = numA.im - numB.im;
	return res;
}

Complex Mul(Complex numA, Complex numB) {
	Complex res;
	res.re = (numA.re * numB.re) - (numA.im * numB.im);
	res.im = (numA.re * numB.im) + (numB.re * numA.im);
	return res;
}

void PrintComplex(Complex num) {
	std::cout << num.re << " + " << num.im << "i" << std::endl;
}

int main()
{
	Complex ex;
	ex.re = 12.6f;
	ex.im = 7.89f;

	Complex ex2;
	ex2.re = 120.45f;
	ex2.im = 19.03f;

	std::cout << AbsoluteValue(ex) << "\n";

	PrintComplex(ComplexConjugate(ex));
	PrintComplex(Add(ex, ex2));
	PrintComplex(Sub(ex, ex2));
	PrintComplex(Mul(ex, ex2));
}