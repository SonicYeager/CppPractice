#pragma once
#include "InternalTypes.h"

namespace TOOLBOX
{
	template<typename Type>
	class TOOLBOX_API Ressource
	{
	public:
		virtual Type Read(const Path&) = 0;
		virtual void Write(const Path&, const Type&) = 0;
		virtual ~Ressource() = default;
	};

	template<typename Type>
	class TOOLBOX_API UI
	{
	public:
		virtual ~UI() = default;
	};
}
