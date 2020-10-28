#include "gmock/gmock.h"
#include "gtest/gtest.h"
#include "NBackLogic.h"

using namespace std::chrono_literals;

class MockConsole
{
public:
	MOCK_METHOD(void, DisplayStimuli, (char c, int i, const std::chrono::milliseconds& ms));
};

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
		"Start: Thu Jan  1 01:00:00 1970",
		"Stimuli: TLHCHSCCQLCKLHC",
		"Answers: NNNNNNJNNNJNJNN"
	};
	EXPECT_EQ(actual, expected);
}

TEST(TestNBackLogic, UpdateDisplay_StimuliDuration5Milliseconds_ShowRemainingTime)
{
	NBACK::NBackLogic log{};
	log.SetUpdateInterval(1ms);
	NBACK::TestConfig tconf{};
	tconf.stimuliIntervall = 5ms;
	log.SetData(tconf);
	::testing::StrictMock<MockConsole> con{};
	::testing::InSequence seq;
	EXPECT_CALL(con, DisplayStimuli(::testing::_, ::testing::_, std::chrono::milliseconds(5)));
	EXPECT_CALL(con, DisplayStimuli(::testing::_, ::testing::_, std::chrono::milliseconds(4)));
	EXPECT_CALL(con, DisplayStimuli(::testing::_, ::testing::_, std::chrono::milliseconds(3)));
	EXPECT_CALL(con, DisplayStimuli(::testing::_, ::testing::_, std::chrono::milliseconds(2)));
	EXPECT_CALL(con, DisplayStimuli(::testing::_, ::testing::_, std::chrono::milliseconds(1)));

	log.UpdateDisplay(std::bind(&MockConsole::DisplayStimuli, std::ref(con), std::placeholders::_1, std::placeholders::_2, std::placeholders::_3), 'c');
}

TEST(TestNBackLogic, UpdateDisplay_TwoStimuli_ShowPresentedStimuliCount)
{
	NBACK::NBackLogic log{};
	::testing::StrictMock<MockConsole> con{};
	log.SetUpdateInterval(1ms);
	auto onUpdateDisplay = std::bind(&MockConsole::DisplayStimuli, std::ref(con), std::placeholders::_1, std::placeholders::_2, std::placeholders::_3);
	NBACK::TestConfig tconf{};
	tconf.stimuliIntervall = 2ms;
	log.SetData(tconf);
	::testing::InSequence seq;
	EXPECT_CALL(con, DisplayStimuli('c', 0, ::testing::_)).Times(2);
	EXPECT_CALL(con, DisplayStimuli('x', 1, ::testing::_)).Times(2);

	log.UpdateDisplay(onUpdateDisplay, 'c');
	log.UpdateDisplay(onUpdateDisplay, 'x');
}