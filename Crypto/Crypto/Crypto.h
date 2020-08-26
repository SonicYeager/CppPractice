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
	ErrorCode Run(int, const char*[]);

	enum class Algorithm
	{
		None,
		CeasarEncode,
		CeasarDecode,
		Last
	};

	void Parse(int, const char*[], Algorithm&, int&, char*&);
	void ParseCount(const char*, int&);
	void ParseAlgorithm(const char*, Algorithm&);
	void ParseFilename(const char*, char*&);
	void ValidateInput(Algorithm, int, const char*);
	void Process(Algorithm, char*, size_t, int);
	void Encode(char*, size_t, int);
	void Decode(char*, size_t, int);
	void PrintError(ErrorCode, const char*);
}; // namespace Crypto
