#include "Logger.h"


namespace LOGGER
{
	Logger::Logger(const std::string& name, Writer* wrtr)	
		: name(name), writer(wrtr)
	{}

	void Logger::Log(PRIORITY prio, const std::string& msg)
	{
		std::string formatted{};
		if(msg == "")
			formatted = "[" + prios[prio] + "]" + prioSeperationSpace[prio] + "[" + name + "]";
		else
			formatted = "[" + prios[prio] + "]" + prioSeperationSpace[prio] + "[" + name + "]" + "  >>" + msg + "<<";
		writer->Write(formatted);
	}
}
