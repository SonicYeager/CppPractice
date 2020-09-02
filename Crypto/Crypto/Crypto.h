#pragma once

enum ErrorCode
{
	SUCCESS,
	NO_INPUT,
	WRONG_PARAMETER,
	OPEN_FILE_FAILED,
	READ_FILE_FAILED,
	WRITE_FILE_FAILED,
	UNKNOWN_ALGORITHM
};

namespace Crypto
{
	void Run(int /*argc*/, const char* /*argv*/[]);

	enum class Algorithm
	{
		None,
		CeasarEncode,
		CeasarDecode,
		Last
	};

	void Parse(int /*argc*/, const char* /*argv*/[], Algorithm& /*algo*/, int& /*shiftCount*/, char*& /*pFilename*/);
	void ParseCount(const char* /*countString*/, int& /*result*/);
	void ParseAlgorithm(const char* /*algoString*/, Algorithm& /*result*/);
	void ParseFilename(const char* /*filename*/, char*& /*pResult*/);
	void ValidateInput(Algorithm /*algo*/, int /*shiftCount*/, const char* /*filename*/);
	void Process(Algorithm /*algo*/, char* /*pBuffer*/, size_t /*size*/, int /*shiftCount*/);
	void Encode(char* /*pBuffer*/, size_t /*size*/, int /*shiftCount*/);
	void Decode(char* /*pBuffer*/, size_t /*size*/, int /*shiftCount*/);
	void PrintError(ErrorCode /*err*/, const char* /*pMsg*/);
}; // namespace Crypto
