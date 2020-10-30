#include "FileHandler.h"

namespace TOOLBOX
{
	namespace FILE
	{
		namespace READER
		{
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
				input.open(filename);
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

			//TemplateExports
			class TOOLBOX_API LinesReader;
		}

		namespace WRITER
		{
			void LinesWriter::Write(const Lines& lines)
			{
				for (auto& line : lines)
					output << line;
				output << std::endl;
			}

			void LinesWriter::Open(const Path& filename)
			{
				output.open(filename);
			}

			LinesWriter::~LinesWriter()
			{
				output.close();
			}

			//TemplateExports
			class TOOLBOX_API LinesWriter;
		}

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

		//TemplateExports
		template class TOOLBOX_API File<Lines>;
	}
}