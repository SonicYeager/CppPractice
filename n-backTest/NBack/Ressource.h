#pragma once
#include "InternalTypes.h"

namespace NBACK
{
	class NBACK_API Ressource
	{
	public:
		virtual Lines ReadFromFile(const Path&) = 0;
		virtual void WriteToFile(const Path&, const Lines&) = 0;
		virtual ~Ressource() = default;
	};
}