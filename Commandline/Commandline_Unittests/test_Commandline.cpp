#include "gmock/gmock.h"
#include "gtest/gtest.h"
#include "Commandline.h"

class MockEventListener
{
public:
	MOCK_METHOD(void, OnNumber, (const int& num));
	MOCK_METHOD(void, OnText, (const std::string& msg));
	MOCK_METHOD(void, OnTextList, (const std::vector<std::string>& texts));
	MOCK_METHOD(void, OnMoney, (const double& mn));
	MOCK_METHOD(void, OnHelp, ());
	MOCK_METHOD(void, OnError, (const std::string& err));
};

class TestCommandEventTrigger : public ::testing::Test
{
protected:
	::testing::StrictMock<MockEventListener> evntLst{};
	COMMANDLINE::CommandEventTrigger cmdEvntTrgr{};
	::testing::InSequence seq;
	virtual void SetUp()
	{
		cmdEvntTrgr.onNumber = std::bind(&MockEventListener::OnNumber, &evntLst, std::placeholders::_1);
		cmdEvntTrgr.onText = std::bind(&MockEventListener::OnText, &evntLst, std::placeholders::_1);
		cmdEvntTrgr.onTextList = std::bind(&MockEventListener::OnTextList, &evntLst, std::placeholders::_1);
		cmdEvntTrgr.onMoney = std::bind(&MockEventListener::OnMoney, &evntLst, std::placeholders::_1);
		cmdEvntTrgr.onError = std::bind(&MockEventListener::OnError, &evntLst, std::placeholders::_1);
		cmdEvntTrgr.onHelp = std::bind(&MockEventListener::OnHelp, &evntLst);
	}
};

TEST_F(TestCommandEventTrigger, Trigger_HelpArg_HelpEvent)
{
	//setup
	EXPECT_CALL(evntLst, OnHelp());

	//excution
	cmdEvntTrgr.Trigger({"--h"});
}

TEST_F(TestCommandEventTrigger, Trigger_NoCommandArgs_CallOnHelp)
{
	//setup
	EXPECT_CALL(evntLst, OnHelp());

	//excution
	cmdEvntTrgr.Trigger({ });
}

TEST_F(TestCommandEventTrigger, Trigger_Number5_CallOnNumber)
{
	//setup
	EXPECT_CALL(evntLst, OnNumber(5));

	//excution
	cmdEvntTrgr.Trigger({"--n", "5" });
}

TEST_F(TestCommandEventTrigger, Trigger_TextHello_CallOnText)
{
	//setup
	EXPECT_CALL(evntLst, OnText("Hello"));

	//excution
	cmdEvntTrgr.Trigger({"--t", "Hello" });
}

TEST_F(TestCommandEventTrigger, Trigger_TextListHello_TextListEvent)
{
	//setup
	EXPECT_CALL(evntLst, OnTextList(std::vector<std::string>{"Hello", "Hello"}));

	//excution
	cmdEvntTrgr.Trigger({"--tl", "Hello", "Hello" });
}

TEST_F(TestCommandEventTrigger, Trigger_Money4Dot5_MoneyEvent)
{
	//setup
	EXPECT_CALL(evntLst, OnMoney(4.5));

	//excution
	cmdEvntTrgr.Trigger({"--m", "4.5"});
}

TEST_F(TestCommandEventTrigger, Trigger_Nonsense_ErrorEvent)
{
	//setup
	EXPECT_CALL(evntLst, OnError("--dasgdfsm"));

	//excution
	cmdEvntTrgr.Trigger({ "--dasgdfsm", "lkdfnv-" });
}

TEST_F(TestCommandEventTrigger, Trigger_Number5AndNumber6_TwoCalls)
{
	//setup
	EXPECT_CALL(evntLst, OnNumber(5));
	EXPECT_CALL(evntLst, OnNumber(6));

	//excution
	cmdEvntTrgr.Trigger({ "--n", "5", "--n", "6"});
}

TEST_F(TestCommandEventTrigger, Trigger_TextHelloAndBye_TwoCalls)
{
	//setup
	EXPECT_CALL(evntLst, OnText("Hello"));
	EXPECT_CALL(evntLst, OnText("Bye"));

	//excution
	cmdEvntTrgr.Trigger({ "--t", "Hello", "--t", "Bye" });
}

TEST_F(TestCommandEventTrigger, Trigger_TextListHelloTwice_TwoCalls)
{
	//setup
	EXPECT_CALL(evntLst, OnTextList(std::vector<std::string>{"Hello", "Hello"}));
	EXPECT_CALL(evntLst, OnTextList(std::vector<std::string>{"Hello", "Hello"}));

	//excution
	cmdEvntTrgr.Trigger({ "--tl", "Hello", "Hello", "--tl", "Hello", "Hello" });
}

TEST_F(TestCommandEventTrigger, Trigger_Money4Dot5And10Dot6_TwoCalls)
{
	//setup
	EXPECT_CALL(evntLst, OnMoney(4.5));
	EXPECT_CALL(evntLst, OnMoney(10.6));

	//excution
	cmdEvntTrgr.Trigger({ "--m", "4.5", "--m", "10.6" });
}

TEST_F(TestCommandEventTrigger, Trigger_AllCmdsOnce_MultipleCalls)
{
	//setup
	EXPECT_CALL(evntLst, OnError("--j"));
	EXPECT_CALL(evntLst, OnNumber(4));
	EXPECT_CALL(evntLst, OnText("Some big Test!"));
	EXPECT_CALL(evntLst, OnTextList(std::vector<std::string>{"Some", "Big", "Test"}));
	EXPECT_CALL(evntLst, OnMoney(5.8));

	//excution
	cmdEvntTrgr.Trigger({"--j", "--n", "4", "--t", "Some big Test!", "--tl", "Some", "Big", "Test", "--m", "5.8" });
}