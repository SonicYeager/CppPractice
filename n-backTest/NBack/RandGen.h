#pragma once
#include "InternalTypes.h"

namespace NBACK
{
	class NBACK_API RandGen
	{
	public:
		virtual std::vector<char> GenNBackChars(const int&, const int&) = 0;
		virtual ~RandGen() = default;
	};
}