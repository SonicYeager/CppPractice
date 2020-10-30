#pragma once
#include "Contracts.h"
#include <fstream>

namespace TOOLBOX
{
	namespace FILE
	{

		using Line = std::string;

		namespace READER
		{
			template<typename Type>
			struct TOOLBOX_API Reader
			{
				virtual void Open(const Path&) = 0;
				virtual Type Read() = 0;
				virtual bool IsNotEOF() = 0;
				~Reader() = default;
			};

#pragma region LineReader
			struct TOOLBOX_API LinesReader : public Reader<Lines>
			{
				void Open(const Path&) override;
				Lines Read() override;
				bool IsNotEOF() override;
				~LinesReader();
			private:
				std::ifstream input;
			};
#pragma endregion
		}

		namespace WRITER
		{
			template<typename Type>
			struct TOOLBOX_API Writer
			{
				virtual void Open(const Path&) = 0;
				virtual void Write(const Type&) = 0;
				~Writer() = default;
			};

#pragma region LineWriter
			struct TOOLBOX_API LinesWriter : public Writer<Lines>
			{

				void Write(const Lines&) override;
				void Open(const Path&) override;
				~LinesWriter();
			private:
				std::ofstream output;
			};
#pragma endregion
		}

		template<typename Type>
		class TOOLBOX_API File : public Ressource<Type>
		{
		public:
			File(READER::Reader<Type>&, WRITER::Writer<Type>&);
			Type Read(const Path& filename) override;
			void Write(const Path& filename, const Type& table) override;

		private:
			READER::Reader<Type>& reader{};
			WRITER::Writer<Type>& writer{};
		};
	}
}