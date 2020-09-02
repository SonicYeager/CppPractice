// This is a personal academic project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++, C#, and Java: http://www.viva64.com

#include "Exceptions.h"

void ParseException::Print()
{
	std::cout << "Parsing Failed: Cause: " << mp_CauseOfException << "; On Line: " << m_lineOfCodeNumber << "; In File: "<< mp_FileName << std::endl;
}

void ValidationFailedException::Print()
{
	std::cout << "Validation Failed: Cause: " << mp_CauseOfException << "; On Line: " << m_lineOfCodeNumber << "; In File: " << mp_FileName << std::endl;
}

void ShiftCountValidationFailedException::Print()
{
	std::cout << "Shift Count Validation Failed: Cause: " << mp_CauseOfException << "; shiftcount value was: " << m_arg <<"; On Line: " << m_lineOfCodeNumber << "; In File: " << mp_FileName << std::endl;
}

void AlgoValidationFailedException::Print()
{
	std::cout << "Algo Validation Failed: Cause: " << mp_CauseOfException << "; algovalue value was: " << static_cast<int>(m_algo) << "; On Line: " << m_lineOfCodeNumber << "; In File: " << mp_FileName << std::endl;
}

void OpenFileFailedException::Print()
{
	std::cout << "Open File Failed: Cause: " << mp_CauseOfException << "; filename value was: " << mp_fname << "; filemode value was: " << mp_fmode <<"; On Line: " << m_lineOfCodeNumber << "; In File: " << mp_FileName << std::endl;
}

BaseException::BaseException(int lineOfCodeNumber, const char* causeOfException, const char* errorCodeFile) :
	m_lineOfCodeNumber(lineOfCodeNumber), mp_CauseOfException(causeOfException), mp_FileName(errorCodeFile)
{}

void BaseException::Print()
{
	std::cout << "Parsing Failed: Cause: " << mp_CauseOfException << "; On Line: " << m_lineOfCodeNumber << "; In File: " << mp_FileName << std::endl;
}

void CopyingIntoNotAllocatedMemoryException::Print()
{
	std::cout << "Copying Into Not Allocated Memory: Cause: " << mp_CauseOfException << "; string value was: " << m_arg << "; On Line: " << m_lineOfCodeNumber << "; In File: " << mp_FileName << std::endl;
}
