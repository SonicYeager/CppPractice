#include "Commandline.h"
#include <map>

namespace COMMANDLINE
{
	inline bool IsEnd(const std::vector<std::string>::iterator& iter, const std::vector<std::string>& temp)
	{
		return iter == temp.end();
	}

	inline bool Contains(const std::string& pred, const std::vector<std::string>::iterator& iter, const std::vector<std::string>& temp)
	{
		return iter->find(pred) != std::string::npos;
	}

	std::vector<std::pair<std::string, std::vector<std::string>>> ParseCmdAndArgs(const std::vector<std::string>& args)
	{
		std::vector<std::pair<std::string, std::vector<std::string>>> res{};
		std::vector<std::string> temp{args};
		std::vector<std::string>::iterator iter = temp.begin();

		while (!IsEnd(iter, temp))
		{
			if (Contains("--", iter, temp))
			{
				std::vector<std::string> args{};
				std::string cmd{*iter};
				if(!IsEnd(iter, temp))
					++iter;
				while (!IsEnd(iter, temp) && !Contains("--", iter, temp))
				{
					args.push_back(*iter);
					if (!IsEnd(iter, temp))
						++iter;
				}
				if (args.size() > 0)
					res.push_back(std::make_pair(cmd, args));
			}
			if (!IsEnd(iter, temp))
				++iter;
		}
		return res;
	}

	void CommandEventTrigger::Trigger(const std::vector<std::string>& args)
	{
		auto parsed = ParseCmdAndArgs(args);
		for (const auto& cmd : parsed)
		{
			if (cmd.first == "--n")
			{
				for (const auto& args : cmd.second)
					onNumber(std::stoi(args));
			}
			else if (cmd.first == "--t")
			{
				for (const auto& args : cmd.second)
					onText(args);
			}
			else if (cmd.first == "--tl")
			{
				onTextList(cmd.second);
			}
			else if (cmd.first == "--m")
			{
				for (const auto& args : cmd.second)
					onMoney(std::stod(args));
			}
			else if (cmd.first == "--h")
			{
				onHelp();
			}
			else
			{
				onError(cmd.first);
			}
		}
	}
}
