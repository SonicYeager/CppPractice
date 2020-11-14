#include <iostream>
#include <ostream>
#include "Expression.h"
#include "Const.h"
#include "Result.h"
#include "Add.h"
#include "Sub.h"
#include "Mul.h"
#include "Div.h"

// - + 7.5 / / 5.5 * 4.3 + 3 2.2 - 2.18 3.5 / * 14 35 123.5

using namespace std;

double GetNum(const char& string)
{
	double num = 0;
	switch(string)
	{
	case '0':
		num = 0;
		break;
	case '1':
		num = 1;
		break;
	case '2':
		num = 2;
		break;
	case '3':
		num = 3;
		break;
	case '4':
		num = 4;
		break;
	case '5':
		num = 5;
		break;
	case '6':
		num = 6;
		break;
	case '7':
		num = 7;
		break;
	case '8':
		num = 8;
		break;
	case '9':
		num = 9;
		break;
	default:
		return num;
		break;
	}

	return num;
}

double GetNum(const char*& string)
{
	double num = 0;

	if(string[0] == ' ')
	{
		string++;
	}

	while(*string != ' ' && (*string != '*' && *string != '/' && *string != '+' && *string != '-' && *string != '.'))
	{
		if(*string == '\0')
		{
			break;
		}
		num += GetNum(*string);
		num *= 10;
		string++;
	}

	num /= 10;

	if(*string == '.')
	{
		string++;
		int counterForDecimals = 1;
		while(*string != ' ' && (*string != '*' && *string != '/' && *string != '+' && *string != '-'))
		{
			if(*string == '\0')
			{
				break;
			}
			double DecimalNum = GetNum(*string);
			DecimalNum /= pow(10, counterForDecimals);
			num += DecimalNum;
			counterForDecimals++;
			string++;
		}
	}

	return num;
}

Result SubParse(const char*& string)
{
	//+ * + 1 2 3 * 4 + 5 6
	double firstNum = 0;
	double secondNum = 0;

	if(string[0] == ' ')
	{
		string++;
	}

	if(*string == '\0')
	{
		return Result(new Const(0));
	}
	else
	{
		if(*string == '*')
		{
			string++;
			firstNum = GetNum(string);
			secondNum = GetNum(string);
			if(firstNum == 0 && secondNum == 0)
			{
				return new Result(new Mul(new Result(SubParse(string)), new Result(SubParse(string))));
			}
			if(firstNum == 0)
			{
				return new Result(new Mul(new Result(SubParse(string)), new Const(secondNum)));
			}
			else if(secondNum == 0)
			{
				return new Result(new Mul(new Const(firstNum), new Result(SubParse(string))));
			}
			else
			{
				return new Result(new Mul(new Const(firstNum), new Const(secondNum)));
			}
		}
		else if(*string == '/')
		{
			string++;
			firstNum = GetNum(string);
			secondNum = GetNum(string);

			if(firstNum == 0 && secondNum == 0)
			{
				return new Result(new Div(new Result(SubParse(string)), new Result(SubParse(string))));
			}
			if(firstNum == 0)
			{
				return new Result(new Div(new Result(SubParse(string)), new Const(secondNum)));
			}
			else if(secondNum == 0)
			{
				return new Result(new Div(new Const(firstNum), new Result(SubParse(string))));
			}
			else
			{
				return new Result(new Div(new Const(firstNum), new Const(secondNum)));
			}
		}
		else if(*string == '-')
		{
			string++;
			firstNum = GetNum(string);
			secondNum = GetNum(string);

			if(firstNum == 0 && secondNum == 0)
			{
				return new Result(new Sub(new Result(SubParse(string)), new Result(SubParse(string))));
			}
			if(firstNum == 0)
			{
				return new Result(new Sub(new Result(SubParse(string)), new Const(secondNum)));
			}
			else if(secondNum == 0)
			{
				return new Result(new Sub(new Const(firstNum), new Result(SubParse(string))));
			}
			else
			{
				return new Result(new Sub(new Const(firstNum), new Const(secondNum)));
			}
		}
		else if(*string == '+')
		{
			string++;
			firstNum = GetNum(string);
			secondNum = GetNum(string);

			if(firstNum == 0 && secondNum == 0)
			{
				return new Result(new Add(new Result(SubParse(string)), new Result(SubParse(string))));
			}
			if(firstNum == 0)
			{
				return new Result(new Add(new Result(SubParse(string)), new Const(secondNum)));
			}
			else if(secondNum == 0)
			{
				return new Result(new Add(new Const(firstNum), new Result(SubParse(string))));
			}
			else
			{
				return new Result(new Add(new Const(firstNum), new Const(secondNum)));
			}
		}
		else
		{
			return new Result(new Const(GetNum(string)));
		}
	}
}

Result Parse(const char* string)
{ //- + 7.5 / / 5.5 * 4.3 + 3 2.2 - 2.18 3.5 / * 14 35 123.5
	//+ * + 1 2 3 * 4 + 5 6
	double firstNum = 0;
	double secondNum = 0;

	if(string[0] == ' ')
	{
		string++;
	}

	if(*string == '\0')
	{
		return Result(new Const(0));
	}
	else
	{
		if(*string == '*')
		{
			string++;
			firstNum = GetNum(string);
			secondNum = GetNum(string);
			if(firstNum == 0 && secondNum == 0)
			{
				return new Result(new Mul(new Result(SubParse(string)), new Result(SubParse(string))));
			}
			if(firstNum == 0)
			{
				return new Result(new Mul(new Result(SubParse(string)), new Const(secondNum)));
			}
			else if(secondNum == 0)
			{
				return new Result(new Mul(new Const(firstNum), new Result(SubParse(string))));
			}
			else
			{
				return new Result(new Mul(new Const(firstNum), new Const(secondNum)));
			}
		}
		else if(*string == '/')
		{
			string++;
			firstNum = GetNum(string);
			secondNum = GetNum(string);

			if(firstNum == 0 && secondNum == 0)
			{
				return new Result(new Div(new Result(SubParse(string)), new Result(SubParse(string))));
			}
			if(firstNum == 0)
			{
				return new Result(new Div(new Result(SubParse(string)), new Const(secondNum)));
			}
			else if(secondNum == 0)
			{
				return new Result(new Div(new Const(firstNum), new Result(SubParse(string))));
			}
			else
			{
				return new Result(new Div(new Const(firstNum), new Const(secondNum)));
			}
		}
		else if(*string == '-')
		{
			string++;
			firstNum = GetNum(string);
			secondNum = GetNum(string);

			if(firstNum == 0 && secondNum == 0)
			{
				return new Result(new Sub(new Result(SubParse(string)), new Result(SubParse(string))));
			}
			if(firstNum == 0)
			{
				return new Result(new Sub(new Result(SubParse(string)), new Const(secondNum)));
			}
			else if(secondNum == 0)
			{
				return new Result(new Sub(new Const(firstNum), new Result(SubParse(string))));
			}
			else
			{
				return new Result(new Sub(new Const(firstNum), new Const(secondNum)));
			}
		}
		else if(*string == '+')
		{
			string++;
			firstNum = GetNum(string);
			secondNum = GetNum(string);

			if(firstNum == 0 && secondNum == 0)
			{
				return new Result(new Add(new Result(SubParse(string)), new Result(SubParse(string))));
			}
			if(firstNum == 0)
			{
				return new Result(new Add(new Result(SubParse(string)), new Const(secondNum)));
			}
			else if(secondNum == 0)
			{
				return new Result(new Add(new Const(firstNum), new Result(SubParse(string))));
			}
			else
			{
				return new Result(new Add(new Const(firstNum), new Const(secondNum)));
			}
		}
		else
		{
			return new Result(new Const(GetNum(string)));
		}
	}
}

int main()
{
	Result result(new Mul(new Const(3), new Add(new Const(2), new Const(9))));
	cout << result.Print(cout) << " = " << result.Evaluate() << std::endl;

	Result* subI = new Result(new Sub(new Const(25), new Const(109)));
	Result* divI = new Result(new Div(new Const(-27), new Const(4.5)));
	Result* addI = new Result(new Add(new Const(1), divI));
	Result* mul = new Result(new Mul(subI, addI));
	Result* div = new Result(new Div(mul, new Const(12)));
	Result add(new Add(div, new Const(5.5)));

	cout << add.Print(cout) << " = " << add.Evaluate() << std::endl;

	const char* input = nullptr;
	char chr[255];
	cin.getline(chr, 255);
	input = chr;

	Result res(Parse(input));

	cout << res.Print(cout) << " = " << res.Evaluate() << std::endl;
}
