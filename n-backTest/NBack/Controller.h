#pragma once
#include "InternalTypes.h"
#include "Logic.h"
#include "RandGen.h"
#include "UI.h"
#include "Ressource.h"

namespace NBACK
{
	class NBACK_API Controller
	{
	public:
		Controller(Logic&, Ressource&, RandGen&, UI&);
		void Run();
	private:
		Logic& logic;
		Ressource& ress;
		RandGen& rgen;
		UI& ui;
	};
}

