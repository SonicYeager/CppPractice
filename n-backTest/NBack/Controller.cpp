#include "Controller.h"

namespace NBACK
{
	Controller::Controller(Logic& log, Ressource& ress, RandGen& rgen, UI& ui) 
		: logic(log), ress(ress), rgen(rgen), ui(ui)
	{}

	void Controller::Run()
	{
		auto tdata = ui.GetUserInput();
		tdata.stimuli = rgen.RandChars(tdata.countStimuli, tdata.n);
		auto start = ui.DisplayYesNoQuestion("Start the Test?");
		if (start == true)
		{
			int index{};
			REACTION reaction;
			logic.SetStartTime(std::chrono::system_clock::now());
			while (index < tdata.countStimuli && (reaction = ui.GetReaction(tdata.stimuliIntervall, tdata.stimuli[index])) != REACTION::ESC)
			{
				logic.RecordStimuli(reaction == REACTION::SPACEBAR ? true : false);
				++index;
			}
			auto fdata = logic.GetAllTestData();
			ress.WriteToFile(INTERNALPATH, fdata);
			auto edata = logic.EvaluateTest();
			ui.DisplayResults(edata);
		}
	}
}