#pragma once
#include <string>
#include <map>

#ifdef LOGGER_EXPORTS
#define LOGGER_API __declspec(dllexport)
#else
#define LOGGER_API __declspec(dllimport)
#endif

namespace LOGGER
{
	class LOGGER_API Writer
	{	
	public:
		virtual void Write(const std::string&) = 0;
		virtual ~Writer() = default;
	};

	enum class LOGGER_API PRIORITY
	{
		INFO = 0,
		WARNING,
		FATAL
	};

	class LOGGER_API Logger
	{
	public:
		Logger(const std::string&, Writer*);
		void Log(PRIORITY, const std::string&);
	private:
		std::string name;
		Writer* writer;
		std::map<PRIORITY, std::string> prios
		{
			{PRIORITY::INFO, "INFO"},
			{PRIORITY::WARNING, "WARNING"}, 
			{PRIORITY::FATAL, "FATAL"} 
		};
		std::map<PRIORITY, std::string> prioSeperationSpace
		{
			{PRIORITY::INFO, "     "},
			{PRIORITY::WARNING, "  "},
			{PRIORITY::FATAL, "    "}
		};
	};
}