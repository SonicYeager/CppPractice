#include "NBackLogic.h"

namespace NBACK
{
	void NBackLogic::SetData(const TestConfig& tdata)
	{
		this->edata.tdata = tdata;
	}

	void NBackLogic::RecordStimuli(const bool& response)
	{
		edata.answers.push_back(response);
	}

	Lines NBackLogic::GetAllTestData()
	{
		Lines res{};

		res.push_back("Subject: " + edata.tdata.subjectname);
		res.push_back("Time of Stimuli: " + std::to_string(edata.tdata.stimuliIntervall.count()));
		res.push_back("N: " + std::to_string(edata.tdata.n));
		std::time_t t = std::chrono::system_clock::to_time_t(edata.startTime);
		char c[26]{};
		ctime_s(c, 26, &t);
		res.push_back("Start: " + std::string(c));
		res.back().pop_back();
		std::string stims{};
		for (auto stim : edata.tdata.stimuli)
			stims += stim;
		res.push_back("Stimuli: " + stims);
		std::string answs{};
		for (auto answ : edata.answers)
			if (answ == true)
				answs += 'J';
			else
				answs += 'N';
		res.push_back("Answers: " + answs);

		return res;
	}

	EvalData NBackLogic::EvaluateTest()
	{
		int correctCount{};
		for (int i{}; i < edata.tdata.n; ++i)
			if (edata.answers.size() > i && edata.answers[i] == false)
				++correctCount;
		for (int i{ edata.tdata.n}; i < edata.answers.size(); ++i)
		{
			auto res = edata.tdata.stimuli[i - edata.tdata.n] == edata.tdata.stimuli[i];
			if (res == edata.answers[i])
				++correctCount;
		}
		edata.percentCorrect = ((correctCount*100) / (edata.answers.size()));
		return edata;
	}

	void NBackLogic::SetStartTime(const std::chrono::system_clock::time_point& startTime)
	{
		edata.startTime = startTime;
	}
}
