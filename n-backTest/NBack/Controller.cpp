#include "Controller.h"

namespace NBACK
{
	Controller::Controller(Logic& log, Ressource& ress, RandGen& rgen, UI& ui) 
		: logic(log), ress(ress), rgen(rgen), ui(ui)
	{}

	void Controller::Run()
	{
		auto tdata = ui.GetUserInput();
		tdata.stimuli = rgen.GenNBackChars(tdata.countStimuli, tdata.n);
		logic.SetData(tdata);
		ui.Countdown(5);
		logic.SetStartTime(std::chrono::system_clock::now());

		auto onReactionSPACEBAR = []() {};
		auto onReactionESC = []() {};
		auto onReactionNOKEY = []() {};

		for ( auto c : tdata.stimuli)
		{
			ui.DisplayStimuli(c);
			REACTION reaction;
			if ((reaction = ui.GetReaction(tdata.stimuliIntervall)) != REACTION::ESC)
				logic.RecordStimuli(reaction == REACTION::SPACEBAR ? true : false);
			else
				break;
		}
		auto fdata = logic.GetAllTestData();
		ress.WriteToFile(INTERNALPATH, fdata);
		auto edata = logic.EvaluateTest();
		ui.DisplayResults(edata);
	}
}