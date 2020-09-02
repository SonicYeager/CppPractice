#include "pch.h"
#include <iostream>

struct Complex {
	float re = 0;
	float im = 0;
};

auto AbsoluteValue(Complex num) -> float {
	float res;
	return res = sqrt(pow(num.re, 2) + pow(num.im, 2)); //alternativ liese sich auch ein annäherungs algo für wurzelziehen aufsetzen
}

auto ComplexConjugate(Complex num) -> Complex {
	return { num.re, -num.im };
}

auto Add(Complex numA, Complex numB) -> Complex {
	Complex res;
	res.re = numA.re + numB.re;
	res.im = numA.im + numB.im;
	return res;
}

auto Sub(Complex numA, Complex numB) -> Complex {
	Complex res;
	res.re = numA.re - numB.re;
	res.im = numA.im - numB.im;
	return res;
}

auto Mul(Complex numA, Complex numB) -> Complex {
	Complex res;
	res.re = (numA.re * numB.re) - (numA.im * numB.im);
	res.im = (numA.re * numB.im) + (numB.re * numA.im);
	return res;
}

void PrintComplex(Complex num) {
	std::cout << num.re << " + " << num.im << "i" << std::endl;
}

auto main() -> int
{
	Complex ex{12.6F, 7.89F};
	Complex ex2{ 120.45F, 19.03F };

	std::cout << AbsoluteValue(ex) << "\n";

	PrintComplex(ComplexConjugate(ex));
	PrintComplex(Add(ex, ex2));
	PrintComplex(Sub(ex, ex2));
	PrintComplex(Mul(ex, ex2));
}