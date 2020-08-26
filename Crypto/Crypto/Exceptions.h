#pragma once

#include <exception>
#include <iostream>


	class BaseException : public std::exception
	{
	public:
		using exception::exception;
		virtual void Print() = 0;
	};

	//NO_INPUT,
	class NoInputException : public BaseException
	{
		public:
			virtual void Print()  override;

	} ;

	//WRONG_PARAMETER
	class WrongParamException : public BaseException
	{
		public:
			virtual void Print()  override;
	} ;

	//UNKNOWN_ALGORITHM
	class UnknownAlgorithmException : public BaseException
	{
		public:
			virtual void Print()  override;
	} ;


