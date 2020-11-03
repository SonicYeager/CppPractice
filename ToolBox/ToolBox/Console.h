#pragma once
#include "Contracts.h"
#include "InternalTypes.h"
#include "Concepts.h"

namespace TOOLBOX
{
	template<typename Type>
	requires streamable<Type>
	class CommandLine : public Console<Type>
	{
	public:
	};
}

