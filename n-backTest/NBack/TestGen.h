#pragma once
#include "RandGen.h"

namespace NBACK
{
	class NBACK_API TestGen : public RandGen
	{
	public:
		std::vector<char> GenNBackChars(const int&, const int&) override;
	};
}
