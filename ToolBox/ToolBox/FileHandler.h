#pragma once
#include "Contracts.h"
#include "Concepts.h"

namespace TOOLBOX
{
	namespace FILE
	{

		using Line = std::string;

		namespace READER
		{
			struct LinesReader : public Reader<Lines>
			{
				void Open(const Path&) override;
				Lines Read() override;
				bool IsNotEOF() override;
				~LinesReader();
			private:
				std::ifstream input;
			};

			template<typename Type>
			requires serializeable<Type>
			struct ObjectReader : public Reader<Type>
			{
				void Open(const Path&) override;
				Type Read() override;
				bool IsNotEOF() override;
				~ObjectReader();
			private:
				std::ifstream input;
			};

			//LnsRdr
			Lines LinesReader::Read()
			{
				Lines res;
				while (IsNotEOF())
				{
					Line line;
					std::getline(input, line);
					res.push_back(line);
				}
				return res;
			}

			void LinesReader::Open(const Path& filename)
			{
				input.open(filename, std::ios::in);
			}

			LinesReader::~LinesReader()
			{
				input.close();
			}

			bool LinesReader::IsNotEOF()
			{
				bool eof = input.eof();
				return !eof;
			}

			//ObjRdr
			template<typename Type>
			requires serializeable<Type>
			Type ObjectReader<Type>::Read()	//TODO
			{
				Type res;
				input.read((char*)&res, sizeof(res));

				return res;
			}

			template<typename Type>
			requires serializeable<Type>
			void ObjectReader<Type>::Open(const Path& filename)
			{
				input.open(filename, std::ios::in);
			}

			template<typename Type>
			requires serializeable<Type>
			ObjectReader<Type>::~ObjectReader()
			{
				input.close();
			}

			template<typename Type>
			requires serializeable<Type>
			bool ObjectReader<Type>::IsNotEOF()
			{
				bool eof = input.eof();
				return !eof;
			}
		} //export pls

		namespace WRITER
		{
			struct LinesWriter : public Writer<Lines>
			{

				void Write(const Lines&) override;
				void Open(const Path&) override;
				~LinesWriter();
			private:
				std::ofstream output;
			};

			template<typename Type>
			requires serializeable<Type>
			struct ObjectWriter : public Writer<Type>
			{

				void Write(const Type&) override;
				void Open(const Path&) override;
				~ObjectWriter();
			private:
				std::ofstream output;
			};

			//LnsRdr
			void LinesWriter::Write(const Lines& lines)
			{
				for (auto& line : lines)
					output << line;
				output << std::endl;
			}

			void LinesWriter::Open(const Path& filename)
			{
				output.open(filename, std::ios::app);
			}

			LinesWriter::~LinesWriter()
			{
				output.close();
			}

			//ObjRdr
			template<typename Type>
			requires serializeable<Type>
			void ObjectWriter<Type>::Write(const Type& obj)
			{
				auto size = sizeof(obj);
				output.write((char*)&obj, size);
				output << std::endl;
			}

			template<typename Type>
			requires serializeable<Type>
				void ObjectWriter<Type>::Open(const Path& filename)
			{
				output.open(filename, std::ios::app);
			}

			template<typename Type>
			requires serializeable<Type>
				ObjectWriter<Type>::~ObjectWriter()
			{
				output.close();
			}
		} //export pls

		template<typename Type>
		class File : public Ressource<Type>
		{
		public:
			File(READER::Reader<Type>&, WRITER::Writer<Type>&);
			Type Read(const Path&) override;
			void Write(const Path&, const Type&) override;

		private:
			READER::Reader<Type>& reader{};
			WRITER::Writer<Type>& writer{};
		};

		template<typename Type>
		File<Type>::File(READER::Reader<Type>& reader, WRITER::Writer<Type>& writer)
			: reader(reader), writer(writer)
		{ }

		template<typename Type>
		Type File<Type>::Read(const Path& filename)
		{
			Type result;
			reader.Open(filename);
			result = reader.Read();
			return result;
		}

		template<typename Type>
		void File<Type>::Write(const Path& filename, const Type& content)
		{
			writer.Open(filename);
			writer.Write(content);
		}
	}
}