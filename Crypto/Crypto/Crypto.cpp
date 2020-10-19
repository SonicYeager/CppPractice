#include "Crypto.h"
#include "Datei.h"
#include "Puffer.h"
#include "Exceptions.h"
#include <cassert>

void ReadFileContent(const char* filename, char*& pResult, size_t& size);

void Crypto::Run(int argc, const char* argv[])
{
	Algorithm algo{};
	Puffer sourceFilename = Puffer(nullptr);

	try
	{
		int shiftCount = 0;
		Parse(argc, argv, algo, shiftCount, sourceFilename.SetChar());
		ValidateInput(algo, shiftCount, sourceFilename.GetChar()); 

		Puffer buffer = Puffer(nullptr);
		size_t size = 0;
		ReadFileContent(sourceFilename.GetChar(), buffer.SetChar(), size);
		Datei dest = Datei("result.txt", "wb");
		auto fres = dest.GetFile();
		assert( fres != nullptr);
		Process(algo, buffer.GetChar(), size, shiftCount);
		size_t written = fwrite(buffer.GetChar(), sizeof(char), size, dest.GetFile());
		assert(written == size);
	}
	catch (BaseException& ex)
	{
		ex.Print();
		//prorgramm neustarten mit neuer eingabe die erneut vom benutzer abgefragt werden!!
	}
}

void Crypto::Parse(int argc, const char* argv[], Algorithm& algo, int& shiftCount, char*& pFilename)
{
	if(argc < 3) {
		throw NoInputException();
}

	ParseAlgorithm(argv[0], algo);
	ParseCount(argv[1], shiftCount);
	ParseFilename(argv[2], pFilename);
}

void Crypto::ParseAlgorithm(const char* algoString, Algorithm& result)
{
	result = static_cast<Algorithm>(std::atoi(algoString));
}

void Crypto::ParseCount(const char* countString, int& result)
{
	result = std::atoi(countString);
}

void Crypto::ParseFilename(const char* filename, char*& pResult)
{
	size_t len = std::strlen(filename);
	pResult = new char[len + 1]{};
	std::strcpy(pResult, filename);
}

void Crypto::ValidateInput(Algorithm algo, int shiftCount, const char* filename)
{
	if(shiftCount < -25 or 25 < shiftCount)
	{
		PrintError(WRONG_PARAMETER, "Shift count only valid in range[-25, 25]");
		throw WrongParamException();
	}
	size_t len = std::strlen(filename);
	if(len == 0)
	{
		PrintError(WRONG_PARAMETER, "Empty filename");
		throw WrongParamException();
	}
	if(static_cast<int>(Algorithm::Last) < static_cast<int>(algo) or static_cast<int>(algo) < static_cast<int>(Algorithm::None))
	{
		PrintError(WRONG_PARAMETER, "Invalid algorithm");
		throw WrongParamException();
	}
}

void Crypto::Process(Algorithm algo, char* pBuffer, size_t size, int shiftCount)
{
	switch(algo)
	{
	case Algorithm::CeasarEncode:
		{
			Encode(pBuffer, size, shiftCount);
			break;
		}
	case Algorithm::CeasarDecode: 
		{
			Decode(pBuffer, size, shiftCount);
			break;
		}
	default:
		{
			throw UnknownAlgorithmException();
		}
	}
}

void Crypto::Encode(char* pBuffer, size_t size, int shiftCount)
{
	if(pBuffer == nullptr) {
		throw WrongParamException();
}
	if(size == 0) {
		throw WrongParamException();
}

	for(size_t i = 0; i < size; ++i)
	{
		if(pBuffer[i] >= 'a' and pBuffer[i] <= 'z')
		{
			char letter = pBuffer[i] + shiftCount;
			if(letter > 'z') {
				letter -= 26;
}
			if(letter < 'a') {
				letter += 26;
}
			pBuffer[i] = letter;
		}
		else if(pBuffer[i] >= 'A' and pBuffer[i] <= 'Z')
		{
			char letter = pBuffer[i] + shiftCount;
			if(letter > 'Z') {
				letter -= 26;
}
			if(letter < 'A') {
				letter += 26;
}
			pBuffer[i] = letter;
		}
	}
}

void Crypto::Decode(char* pBuffer, size_t size, int shiftCount)
{
	Encode(pBuffer, size, -shiftCount);
}

void Crypto::PrintError(ErrorCode err, const char* pMsg)
{
	std::cout << "Error: " << err << ' ' << pMsg << '\n';
}

void ReadFileContent(const char* pFilename, char*& pResult, size_t& size)
{
	if(pFilename == nullptr) {
		throw WrongParamException();
}

	Datei src = Datei(pFilename, "rb");
	auto fres = src.GetFile();
	assert(fres != nullptr);

	fseek(src.GetFile(), 0, SEEK_END);
	size_t bytes = ftell(src.GetFile());
	rewind(src.GetFile());
	Puffer buffer = Puffer(new char[bytes], true);

	size_t read = fread(buffer.SetChar(), sizeof(char), bytes, src.GetFile());

	assert(read == bytes);
	size = bytes;
	pResult = buffer.GetChar();
}
