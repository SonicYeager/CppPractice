#include "gmock/gmock.h"
#include "gtest/gtest.h"
#include "Commandline.h"

class MockEventListener
{
public:
	MOCK_METHOD(void, NumberEventHandler, (const int& num));
	MOCK_METHOD(void, TextEventHandler, (const std::string& msg));
	MOCK_METHOD(void, TextListEventHandler, (const std::vector<std::string>& texts));
	MOCK_METHOD(void, MoneyEventHandler, (const double& mn));
	MOCK_METHOD(void, HelpEventHandler, ());
	MOCK_METHOD(void, ErrorEventHandler, (const std::string& err));
};

class TestCommandEventTrigger : public ::testing::Test
{
protected:
	::testing::StrictMock<MockEventListener> evntLst{};
	COMMANDLINE::CommandEventTrigger cmdEvntTrgr{};
	::testing::InSequence seq;
	virtual void SetUp()
	{
		cmdEvntTrgr.onNumber = std::bind(&MockEventListener::NumberEventHandler, &evntLst, std::placeholders::_1);
		cmdEvntTrgr.onText = std::bind(&MockEventListener::TextEventHandler, &evntLst, std::placeholders::_1);
		cmdEvntTrgr.onTextList = std::bind(&MockEventListener::TextListEventHandler, &evntLst, std::placeholders::_1);
		cmdEvntTrgr.onMoney = std::bind(&MockEventListener::MoneyEventHandler, &evntLst, std::placeholders::_1);
		cmdEvntTrgr.onError = std::bind(&MockEventListener::ErrorEventHandler, &evntLst, std::placeholders::_1);
		cmdEvntTrgr.onHelp = std::bind(&MockEventListener::HelpEventHandler, &evntLst);
	}
};

TEST_F(TestCommandEventTrigger, Trigger_HelpArg_HelpEvent)
{
	//setup
	EXPECT_CALL(evntLst, HelpEventHandler());

	//excution
	cmdEvntTrgr.Trigger({"--h"});
}

TEST_F(TestCommandEventTrigger, Trigger_Empty_HelpEvent)
{
	//setup
	EXPECT_CALL(evntLst, HelpEventHandler());

	//excution
	cmdEvntTrgr.Trigger({ });
}

TEST_F(TestCommandEventTrigger, Trigger_Number5_NumberEventWithNum)
{
	//setup
	EXPECT_CALL(evntLst, NumberEventHandler(5));

	//excution
	cmdEvntTrgr.Trigger({"--n", "5" });
}

TEST_F(TestCommandEventTrigger, Trigger_TextHello_TextEvent)
{
	//setup
	EXPECT_CALL(evntLst, TextEventHandler("Hello"));

	//excution
	cmdEvntTrgr.Trigger({"--t", "Hello" });
}

TEST_F(TestCommandEventTrigger, Trigger_TextListHello_TextListEvent)
{
	//setup
	EXPECT_CALL(evntLst, TextListEventHandler(std::vector<std::string>{"Hello", "Hello"}));

	//excution
	cmdEvntTrgr.Trigger({"--tl", "Hello", "Hello" });
}

TEST_F(TestCommandEventTrigger, Trigger_Money4Dot5_MoneyEvent)
{
	//setup
	EXPECT_CALL(evntLst, MoneyEventHandler(4.5));

	//excution
	cmdEvntTrgr.Trigger({"--m", "4.5"});
}

TEST_F(TestCommandEventTrigger, Trigger_Nonsense_ErrorEvent)
{
	//setup
	EXPECT_CALL(evntLst, ErrorEventHandler("--dasgdfsm"));

	//excution
	cmdEvntTrgr.Trigger({ "--dasgdfsm", "lkdfnv-" });
}

TEST_F(TestCommandEventTrigger, Trigger_Number5AndNumber6_TwoCalls)
{
	//setup
	EXPECT_CALL(evntLst, NumberEventHandler(5));
	EXPECT_CALL(evntLst, NumberEventHandler(6));

	//excution
	cmdEvntTrgr.Trigger({ "--n", "5", "--n", "6"});
}

TEST_F(TestCommandEventTrigger, Trigger_TextHelloAndBye_TwoCalls)
{
	//setup
	EXPECT_CALL(evntLst, TextEventHandler("Hello"));
	EXPECT_CALL(evntLst, TextEventHandler("Bye"));

	//excution
	cmdEvntTrgr.Trigger({ "--t", "Hello", "--t", "Bye" });
}

TEST_F(TestCommandEventTrigger, Trigger_TextListHelloTwice_TwoCalls)
{
	//setup
	EXPECT_CALL(evntLst, TextListEventHandler(std::vector<std::string>{"Hello", "Hello"}));
	EXPECT_CALL(evntLst, TextListEventHandler(std::vector<std::string>{"Hello", "Hello"}));

	//excution
	cmdEvntTrgr.Trigger({ "--tl", "Hello", "Hello", "--tl", "Hello", "Hello" });
}

TEST_F(TestCommandEventTrigger, Trigger_Money4Dot5And10Dot6_TwoCalls)
{
	//setup
	EXPECT_CALL(evntLst, MoneyEventHandler(4.5));
	EXPECT_CALL(evntLst, MoneyEventHandler(10.6));

	//excution
	cmdEvntTrgr.Trigger({ "--m", "4.5", "--m", "10.6" });
}

TEST_F(TestCommandEventTrigger, Trigger_AllCmdsOnce_MultipleCalls)
{
	//setup
	EXPECT_CALL(evntLst, ErrorEventHandler("--j"));
	EXPECT_CALL(evntLst, NumberEventHandler(4));
	EXPECT_CALL(evntLst, TextEventHandler("Some big Test!"));
	EXPECT_CALL(evntLst, TextListEventHandler(std::vector<std::string>{"Some", "Big", "Test"}));
	EXPECT_CALL(evntLst, MoneyEventHandler(5.8));

	//excution
	cmdEvntTrgr.Trigger({"--j", "--n", "4", "--t", "Some big Test!", "--tl", "Some", "Big", "Test", "--m", "5.8" });
}