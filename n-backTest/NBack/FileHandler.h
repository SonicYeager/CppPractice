#pragma once
#include "Ressource.h"

namespace NBACK
{
	class NBACK_API FileHandler : public Ressource
	{
	public:
		Lines ReadFromFile(const Path& filename) override;
		void WriteToFile(const Path& filename, const Lines& table) override;
	};
}