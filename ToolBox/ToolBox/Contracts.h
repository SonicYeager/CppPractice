#pragma once
#include "InternalTypes.h"

namespace TOOLBOX
{
	template<typename Type>
	class Ressource
	{
	public:
		virtual Type Read(const Path&) = 0;
		virtual void Write(const Path&, const Type&) = 0;
		virtual ~Ressource() = default;
	};

	template<typename Type>
	class Console
	{
	public:
		virtual Type Scan() = 0;
		virtual void Print(const Type&) = 0;
		virtual ~UI() = default;
	};

	template<typename Type>
	struct Reader
	{
		virtual void Open(const Path&) = 0;
		virtual Type Read() = 0;
		virtual bool IsNotEOF() = 0;
		~Reader() = default;
	};

	template<typename Type>
	struct Writer
	{
		virtual void Open(const Path&) = 0;
		virtual void Write(const Type&) = 0;
		~Writer() = default;
	};
}
