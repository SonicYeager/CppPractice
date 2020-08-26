#pragma once
#include <exception>
#include <iostream>


	class BaseException : public std::exception
	{
	public:
		using std::exception::exception;
		BaseException() = default;
		BaseException(int, const char*, const char*);
		virtual void Print();
	protected:
		int m_lineOfCodeNumber{};
		const char* mp_CauseOfException{};
		const char* mp_FileName{};
	};

	class 	ParseException : public BaseException
	{
	public:
		virtual void Print()  override;
		ParseException(int lineOfCodeNumber, const char* causeOfException, const char* errorCodeFile, int arg) : 
			m_arg(arg)
		{
			m_lineOfCodeNumber = lineOfCodeNumber;
			mp_CauseOfException = causeOfException;
			mp_FileName = errorCodeFile;
		}

	private:
		int m_arg{};
	} ;

	class 	CopyingIntoNotAllocatedMemoryException : public BaseException
	{
	public:
		virtual void Print()  override;
		CopyingIntoNotAllocatedMemoryException(int lineOfCodeNumber, const char* causeOfException, const char* errorCodeFile, const char* arg) :
			m_arg(arg)
		{
			m_lineOfCodeNumber = lineOfCodeNumber;
			mp_CauseOfException = causeOfException;
			mp_FileName = errorCodeFile;
		}

	private:
		const char* m_arg{};
	};

	class ValidationFailedException : public BaseException
	{
	public:
		virtual void Print()  override;
		ValidationFailedException(int lineOfCodeNumber, const char* causeOfException, const char* errorCodeFile)
		{
			m_lineOfCodeNumber = lineOfCodeNumber;
			mp_CauseOfException = causeOfException;
			mp_FileName = errorCodeFile;
		}
	} ;

	class ShiftCountValidationFailedException : public BaseException
	{
	public:
		virtual void Print()  override;
		ShiftCountValidationFailedException(int lineOfCodeNumber, const char* causeOfException, const char* errorCodeFile, int arg) :
			m_arg(arg)
		{
			m_lineOfCodeNumber = lineOfCodeNumber;
			mp_CauseOfException = causeOfException;
			mp_FileName = errorCodeFile;
		}

	private:
		int m_arg{};
	};

	class AlgoValidationFailedException : public BaseException
	{
	public:
		virtual void Print()  override;
		AlgoValidationFailedException(int lineOfCodeNumber, const char* causeOfException, const char* errorCodeFile, int algo) :
			m_algo(algo)
		{
			m_lineOfCodeNumber = lineOfCodeNumber;
			mp_CauseOfException = causeOfException;
			mp_FileName = errorCodeFile;
		}

	private:
		int m_algo{};
	};

	class OpenFileFailedException : public BaseException
	{
	public:
		virtual void Print()  override;
		OpenFileFailedException(int lineOfCodeNumber, const char* causeOfException, const char* errorCodeFile, const char* name, const char* mode) :
			mp_fname(name), mp_fmode(mode)
		{
			m_lineOfCodeNumber = lineOfCodeNumber;
			mp_CauseOfException = causeOfException;
			mp_FileName = errorCodeFile;
		}

	private:
		const char* mp_fname{};
		const char* mp_fmode{};
	}; 
