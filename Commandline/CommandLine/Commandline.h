#pragma once
#include <string>
#include <vector>
#include <functional>

#ifdef COMMANDLINE_EXPORTS
#define COMMANDLINE_API __declspec(dllexport)
#else
#define COMMANDLINE_API __declspec(dllimport)
#endif

namespace COMMANDLINE
{
	class COMMANDLINE_API CommandEventTrigger
	{
	public:
		void Trigger(const std::vector<std::string>&);
		std::function<void(const int&)> onNumber;
		std::function<void(const std::string&)> onText;
		std::function<void(const std::vector<std::string>&)> onTextList;
		std::function<void(const double&)> onMoney;
		std::function<void()> onHelp;
		std::function<void(std::string)> onError;
	};
}