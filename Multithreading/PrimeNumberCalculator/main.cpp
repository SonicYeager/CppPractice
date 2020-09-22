#include "Ui.h"
#include "ComputePrimeNumbers.h"
#include "Contracts.h"
#include <vector>

//void StartNewComputation(Range range, Ui& ui)
//{
//	ComputePrimeNumbers logic;
//	auto primes  = logic.ComputePrimes(range);
//	ui.ShowResult(range, primes);
//}
//
//void StartNewGeneratedComputation(Range range, Ui& ui)
//{
//	ComputePrimeNumbers logic;
//	auto id = ui.AddProgress();
//	for(auto prim : logic.ComputePrimesGenerated(range))
//	{
//		ui.UpdateProgress(id, prim);
//	}
//	ui.Finished(id, range);
//}

//solution 3

void StartNewAsyncGeneratedComputation(Range range, Ui& ui)
{

	ComputePrimeNumbers* logic = new ComputePrimeNumbers; 
	auto id = ui.AddProgress();

	auto onFinishLambda = [&ui, id, range, logic]() 
	{
		ui.Finished(id, range);
		delete logic;
	};

	logic->onProgress = std::bind(&Ui::UpdateProgress, &ui, id, std::placeholders::_1); //richtiger ansatz
	logic->onFinish = onFinishLambda;
	logic->ComputePrimesEventAsyncGenerated(range);
}

int main()
{
	Ui ui;
	//ui.onRange = std::bind(StartNewComputation, std::placeholders::_1, std::ref(ui));
	ui.onRange = std::bind(StartNewAsyncGeneratedComputation, std::placeholders::_1, std::ref(ui));

	ui.Run();
	return 0;
}
