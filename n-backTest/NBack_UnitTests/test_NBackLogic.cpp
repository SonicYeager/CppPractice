#include "gmock/gmock.h"
#include "NBackLogic.h"

TEST(TestNBackLogic, EvaluateTest_AllRecordsCorrect_OneHundretPercent)
{
	//setup
	NBACK::TestConfig tdata{3, 15, "Dummy", {'T', 'L' ,'H' ,'C' ,'H' ,'S' ,'C' ,'C' ,'Q' ,'L' ,'C' ,'K' ,'L' ,'H' ,'C'}, std::chrono::milliseconds(50)};
	NBACK::NBackLogic nblog{};
	nblog.SetData(tdata);
	nblog.RecordStimuli(false);
	nblog.RecordStimuli(false);
	nblog.RecordStimuli(false);
	nblog.RecordStimuli(false);
	nblog.RecordStimuli(false);
	nblog.RecordStimuli(false);
	nblog.RecordStimuli(true);
	nblog.RecordStimuli(false);
	nblog.RecordStimuli(false);
	nblog.RecordStimuli(false);
	nblog.RecordStimuli(true);
	nblog.RecordStimuli(false);
	nblog.RecordStimuli(true);
	nblog.RecordStimuli(false);
	nblog.RecordStimuli(false);

	//execute
	auto actual = nblog.EvaluateTest().percentCorrect;

	//eval
	int expected = 100;
	EXPECT_EQ(actual, expected);
}

TEST(TestNBackLogic, EvaluateTest_TwelveOfFifteenCorrect_EightyPercent)
{
	//setup
	NBACK::TestConfig tdata{ 3, 15, "Dummy", {'T', 'L' ,'H' ,'C' ,'H' ,'S' ,'C' ,'C' ,'Q' ,'L' ,'C' ,'K' ,'L' ,'H' ,'C'}, std::chrono::milliseconds(50) };
	NBACK::NBackLogic nblog{};
	nblog.SetData(tdata);
	nblog.RecordStimuli(false);
	nblog.RecordStimuli(false);
	nblog.RecordStimuli(false);
	nblog.RecordStimuli(false);
	nblog.RecordStimuli(false);
	nblog.RecordStimuli(false);
	nblog.RecordStimuli(true);
	nblog.RecordStimuli(false);
	nblog.RecordStimuli(false);
	nblog.RecordStimuli(false);
	nblog.RecordStimuli(true);
	nblog.RecordStimuli(false);
	nblog.RecordStimuli(false);
	nblog.RecordStimuli(true);
	nblog.RecordStimuli(true);

	//execute
	double actual = nblog.EvaluateTest().percentCorrect;

	//eval
	double expected = 80;
	EXPECT_EQ(actual, expected);
}

TEST(TestNBackLogic, EvaluateTest_AllRecordsFalse_ZeroPercent)
{
	//setup
	NBACK::TestConfig tdata{ 3, 15, "Dummy", {'T', 'L' ,'H' ,'C' ,'H' ,'S' ,'C' ,'C' ,'Q' ,'L' ,'C' ,'K' ,'L' ,'H' ,'C'}, std::chrono::milliseconds(50) };
	NBACK::NBackLogic nblog{};
	nblog.SetData(tdata);
	nblog.RecordStimuli(true);
	nblog.RecordStimuli(true);
	nblog.RecordStimuli(true);
	nblog.RecordStimuli(true);
	nblog.RecordStimuli(true);
	nblog.RecordStimuli(true);
	nblog.RecordStimuli(false);
	nblog.RecordStimuli(true);
	nblog.RecordStimuli(true);
	nblog.RecordStimuli(true);
	nblog.RecordStimuli(false);
	nblog.RecordStimuli(true);
	nblog.RecordStimuli(false);
	nblog.RecordStimuli(true);
	nblog.RecordStimuli(true);

	//execute
	auto actual = nblog.EvaluateTest().percentCorrect;

	//eval
	int expected = 0;
	EXPECT_EQ(actual, expected);
}

//second increment
TEST(TestNBackLogic, GetAllTestData_Full3BackTest_ReturnLines)
{
	//setup
	NBACK::TestConfig tdata{ 3, 15, "Dummy", {'T', 'L' ,'H' ,'C' ,'H' ,'S' ,'C' ,'C' ,'Q' ,'L' ,'C' ,'K' ,'L' ,'H' ,'C'}, std::chrono::milliseconds(50) };
	NBACK::NBackLogic nblog{};
	nblog.SetData(tdata);
	std::chrono::system_clock::time_point startTime{};
	std::string strTime{"Thu Jan  1 01:00 : 00 1970\n"};
	nblog.SetStartTime(startTime);
	nblog.RecordStimuli(false);
	nblog.RecordStimuli(false);
	nblog.RecordStimuli(false);
	nblog.RecordStimuli(false);
	nblog.RecordStimuli(false);
	nblog.RecordStimuli(false);
	nblog.RecordStimuli(true);
	nblog.RecordStimuli(false);
	nblog.RecordStimuli(false);
	nblog.RecordStimuli(false);
	nblog.RecordStimuli(true);
	nblog.RecordStimuli(false);
	nblog.RecordStimuli(true);
	nblog.RecordStimuli(false);
	nblog.RecordStimuli(false);

	//execute
	auto actual = nblog.GetAllTestData();

	//eval
	NBACK::Lines expected = 
	{
		"Subject: Dummy",
		"Time of Stimuli: 50",
		"N: 3",
		"Start: Thu Jan  1 01:00:00 1970\n",
		"Stimuli: TLHCHSCCQLCKLHC",
		"Answers: NNNNNNJNNNJNJNN"
	};
	EXPECT_EQ(actual, expected);
}