#include "Controller.h"

namespace NBACK
{
	Controller::Controller(Logic& log, Ressource& ress, RandGen& rgen, UI& ui) 
		: logic(log), ress(ress), rgen(rgen), ui(ui)
	{}


	void onReactionSPACEBAR(Logic& logic)
	{
		logic.RecordStimuli(true);
	}

	void onReactionNOKEY(Logic& logic)
	{
		logic.RecordStimuli(false);
	}

	void onReactionESC(Logic& logic, Ressource& ress, UI& ui)
	{
		auto fdata = logic.GetAllTestData();
		ress.WriteToFile(INTERNALPATH, fdata);
		auto edata = logic.EvaluateTest();
		ui.DisplayResults(edata);
		std::exit(0);
	}

	void Controller::Run()
	{
		auto space = std::bind(onReactionSPACEBAR, std::ref(logic));
		auto nokey = std::bind(onReactionNOKEY, std::ref(logic));
		auto escape = std::bind(onReactionESC, std::ref(logic), std::ref(ress), std::ref(ui));
		auto tdata = ui.GetUserInput();
		tdata.stimuli = rgen.GenNBackChars(tdata.countStimuli, tdata.n);
		logic.SetStartTime(std::chrono::system_clock::now());
		logic.SetData(tdata);
		ui.Countdown(5);
		int presented{};
		for ( auto c : tdata.stimuli)
		{
			ui.DisplayStimuli(c, presented, tdata.stimuliIntervall);
			ui.GetReaction(tdata.stimuliIntervall, space, nokey, escape);
			++presented;
		}
		auto fdata = logic.GetAllTestData();
		ress.WriteToFile(INTERNALPATH, fdata);
		auto edata = logic.EvaluateTest();
		ui.DisplayResults(edata);
	}
}