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

		auto onReactionSPACEBAR = [&]{logic.RecordStimuli(true); };
		auto onReactionNOKEY = [&]() {logic.RecordStimuli(false); };
		auto onReactionESC = [&]() 
		{
			auto fdata = logic.GetAllTestData();
			ress.WriteToFile(INTERNALPATH, fdata);
			auto edata = logic.EvaluateTest();
			ui.DisplayResults(edata);
			std::exit(0);
		};

		for ( auto c : tdata.stimuli)
		{
			ui.DisplayStimuli(c);
			ui.GetReaction(tdata.stimuliIntervall, onReactionSPACEBAR, onReactionNOKEY, onReactionESC);
		}
		auto fdata = logic.GetAllTestData();
		ress.WriteToFile(INTERNALPATH, fdata);
		auto edata = logic.EvaluateTest();
		ui.DisplayResults(edata);
	}
}