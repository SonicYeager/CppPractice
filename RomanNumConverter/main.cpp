#include<assert.h>
#include "RomanConvert.h"

int main() {
	auto val3 = RomanToDecimal("MCDXCII");
	assert(val3 == 1492);
	auto val4 = RomanToDecimal("MDCCCLVI");
	assert(val4 == 1856);
	auto val = DecimalToRoman(1492);
	assert(val == "MCDXCII");
	auto val2 = DecimalToRoman(1856);
	assert(val2 == "MDCCCLVI");
	auto val5 = DecimalToRoman(1000);
	assert(val5 == "M");
}