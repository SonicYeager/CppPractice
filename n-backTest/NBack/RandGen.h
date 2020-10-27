#pragma once
#include "InternalTypes.h"

namespace NBACK
{
	class NBACK_API RandGen
	{
	public:
		virtual std::vector<char> RandChars(const int&, const int&) = 0;
		virtual ~RandGen() = default;
	};
}