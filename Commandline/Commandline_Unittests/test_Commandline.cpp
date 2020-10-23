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

TEST(TestCommandEventTrigger, Trigger_HelpArg_HelpEvent)
{
	//setup
	MockEventListener evntLst{};
	COMMANDLINE::CommandEventTrigger cmdEvntTrgr{};
	cmdEvntTrgr.onHelp = std::bind(&MockEventListener::HelpEventHandler, &evntLst);
	EXPECT_CALL(evntLst, HelpEventHandler());

	//excution
	cmdEvntTrgr.Trigger({"--h", ""});
}

TEST(TestCommandEventTrigger, Trigger_Number5_NumberEventWithNum)
{
	//setup
	MockEventListener evntLst{};
	COMMANDLINE::CommandEventTrigger cmdEvntTrgr{};
	cmdEvntTrgr.onNumber = std::bind(&MockEventListener::NumberEventHandler, &evntLst, std::placeholders::_1);
	EXPECT_CALL(evntLst, NumberEventHandler(5));

	//excution
	cmdEvntTrgr.Trigger({"--n", "5" });
}

TEST(TestCommandEventTrigger, Trigger_TextHello_TextEvent)
{
	//setup
	MockEventListener evntLst{};
	COMMANDLINE::CommandEventTrigger cmdEvntTrgr{};
	cmdEvntTrgr.onText = std::bind(&MockEventListener::TextEventHandler, &evntLst, std::placeholders::_1);
	EXPECT_CALL(evntLst, TextEventHandler("Hello"));

	//excution
	cmdEvntTrgr.Trigger({"--t", "Hello" });
}

TEST(TestCommandEventTrigger, Trigger_TextListHello_TextListEvent)
{
	//setup
	MockEventListener evntLst{};
	COMMANDLINE::CommandEventTrigger cmdEvntTrgr{};
	cmdEvntTrgr.onTextList = std::bind(&MockEventListener::TextListEventHandler, &evntLst, std::placeholders::_1);
	EXPECT_CALL(evntLst, TextListEventHandler(std::vector<std::string>{"Hello", "Hello"}));

	//excution
	cmdEvntTrgr.Trigger({"--tl", "Hello", "Hello" });
}

TEST(TestCommandEventTrigger, Trigger_Money4Dot5_MoneyEvent)
{
	//setup
	MockEventListener evntLst{};
	COMMANDLINE::CommandEventTrigger cmdEvntTrgr{};
	cmdEvntTrgr.onMoney = std::bind(&MockEventListener::MoneyEventHandler, &evntLst, std::placeholders::_1);
	EXPECT_CALL(evntLst, MoneyEventHandler(4.5));

	//excution
	cmdEvntTrgr.Trigger({"--m", "4.5"});
}

TEST(TestCommandEventTrigger, Trigger_Nonsense_ErrorEvent)
{
	//setup
	MockEventListener evntLst{};
	COMMANDLINE::CommandEventTrigger cmdEvntTrgr{};
	cmdEvntTrgr.onError = std::bind(&MockEventListener::ErrorEventHandler, &evntLst, std::placeholders::_1);
	EXPECT_CALL(evntLst, ErrorEventHandler("--dasgdfsm"));

	//excution
	cmdEvntTrgr.Trigger({ "--dasgdfsm", "lkdfnv-" });
}

TEST(TestCommandEventTrigger, Trigger_Number5AndNumber6_TwoCalls)
{
	//setup
	MockEventListener evntLst{};
	COMMANDLINE::CommandEventTrigger cmdEvntTrgr{};
	cmdEvntTrgr.onNumber = std::bind(&MockEventListener::NumberEventHandler, &evntLst, std::placeholders::_1);
	EXPECT_CALL(evntLst, NumberEventHandler(5));

	//excution
	cmdEvntTrgr.Trigger({ "--n", "5" });
}

TEST(TestCommandEventTrigger, Trigger_TextHelloAndBye_TwoCalls)
{
	//setup
	MockEventListener evntLst{};
	COMMANDLINE::CommandEventTrigger cmdEvntTrgr{};
	cmdEvntTrgr.onText = std::bind(&MockEventListener::TextEventHandler, &evntLst, std::placeholders::_1);
	EXPECT_CALL(evntLst, TextEventHandler("Hello"));

	//excution
	cmdEvntTrgr.Trigger({ "--t", "Hello" });
}

TEST(TestCommandEventTrigger, Trigger_TextListHelloTwice_TwoCalls)
{
	//setup
	MockEventListener evntLst{};
	COMMANDLINE::CommandEventTrigger cmdEvntTrgr{};
	cmdEvntTrgr.onTextList = std::bind(&MockEventListener::TextListEventHandler, &evntLst, std::placeholders::_1);
	EXPECT_CALL(evntLst, TextListEventHandler(std::vector<std::string>{"Hello", "Hello"}));

	//excution
	cmdEvntTrgr.Trigger({ "--tl", "Hello", "Hello" });
}

TEST(TestCommandEventTrigger, Trigger_Money4Dot5And10Dot6_TwoCalls)
{
	//setup
	MockEventListener evntLst{};
	COMMANDLINE::CommandEventTrigger cmdEvntTrgr{};
	cmdEvntTrgr.onMoney = std::bind(&MockEventListener::MoneyEventHandler, &evntLst, std::placeholders::_1);
	::testing::InSequence seq;
	EXPECT_CALL(evntLst, MoneyEventHandler(4.5));
	EXPECT_CALL(evntLst, MoneyEventHandler(10.6));

	//excution
	cmdEvntTrgr.Trigger({ "--m", "4.5", "--m", "10.6"});
