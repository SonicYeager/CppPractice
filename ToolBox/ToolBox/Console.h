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
		Type Scan() override; //scan all (or scan line??) collect the available input and stream it into the type (check if casting is necc)
		void Print(const Type&) override;  //just stream out the given type
	};

	template<typename Type>
	requires streamable<Type>
	inline Type CommandLine<Type>::Scan()
	{	
		Type res{};

		return res;
	}

	template<typename Type>
	requires streamable<Type>
	inline void CommandLine<Type>::Print(const Type&)
	{
	}
}

