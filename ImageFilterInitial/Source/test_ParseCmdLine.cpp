#include "gmock/gmock.h"
#include "ParseCmdLine.h"

#pragma region Prepare
class ParseEventFake
{
public:
	MOCK_METHOD1(OnSourceFile, void(const std::string&));
	MOCK_METHOD1(OnDestinationFile, void(const std::string&));
	MOCK_METHOD1(OnChooseKernel, void(const std::string&));
	MOCK_METHOD1(OnScaleFactor, void(float));
	MOCK_METHOD1(OnOrientation, void(const std::string&));
	MOCK_METHOD0(OnNormalize, void());
	MOCK_METHOD0(OnHelp, void());
	MOCK_METHOD2(OnUnsupportedCmd, void(const std::string&, const std::string&));
};

class TestParseCmdLine : public testing::Test
{
public:
	TestParseCmdLine()
	{
		parser.onSourceFile = [this](const std::string& path) { events.OnSourceFile(path); };
		parser.onDestinationFile = [this](const std::string& path) { events.OnDestinationFile(path); };
		parser.onChooseKernel = [this](const std::string& filter) { events.OnChooseKernel(filter); };
		parser.onScaleFactor = [this](float scale) { events.OnScaleFactor(scale); };
		parser.onOrientation = [this](const std::string& orientation) { events.OnOrientation(orientation); };
		parser.onNormalize = [this] { events.OnNormalize(); };
		parser.onHelp = [this] { events.OnHelp(); };
		parser.onUnsupportedCmd = [this](const std::string& cmd, const std::string& arg) {
			events.OnUnsupportedCmd(cmd, arg);
		};
	}

	ParseCmdLine parser;
	testing::StrictMock<ParseEventFake> events;
};
#pragma endregion


TEST_F(TestParseCmdLine, Process_CommandSrc_OnSourceFileCalled)
{
	EXPECT_CALL(events, OnSourceFile("Test.bmp"));

	parser.Process({"-src", "Test.bmp"});
}

TEST_F(TestParseCmdLine, Process_CommandDest_OnDestinationFileCalled)
{
	EXPECT_CALL(events, OnDestinationFile("Test.bmp"));

	parser.Process({"-dest", "Test.bmp"});
}

TEST_F(TestParseCmdLine, Process_CommandScale_OnScaleFactorCalled)
{
	EXPECT_CALL(events, OnScaleFactor(2.25));

	parser.Process({"-scale", "2.25"});
}

TEST_F(TestParseCmdLine, Process_CommandOrient_OnOrientationCalled)
{
	EXPECT_CALL(events, OnOrientation("vertical"));

	parser.Process({"-orient", "vertical"});
}

TEST_F(TestParseCmdLine, Process_CommandKernel_OnChooseKernelCalled)
{
	EXPECT_CALL(events, OnChooseKernel("prewitt"));

	parser.Process({"-kernel", "prewitt"});
}

TEST_F(TestParseCmdLine, Process_CommandNormalize_OnNormalizeCalled)
{
	EXPECT_CALL(events, OnNormalize());

	parser.Process({"-norm"});
}

TEST_F(TestParseCmdLine, Process_CommandHelp_OnHelpCalled)
{
	EXPECT_CALL(events, OnHelp());

	parser.Process({"-help"});
}

TEST_F(TestParseCmdLine, Process_NoCmdLineArgs_OnHelpCalled)
{
	EXPECT_CALL(events, OnHelp());

	parser.Process({});
}

TEST_F(TestParseCmdLine, Process_UnsupportedCommand_OnUnsupportedCmdCalled)
{
	EXPECT_CALL(events, OnUnsupportedCmd("blub", "hihi"));

	parser.Process({"-blub", "hihi"});
}

TEST_F(TestParseCmdLine, Process_MultipleDifferentCommands_MultipleEventsCalled)
{
	testing::InSequence order;
	EXPECT_CALL(events, OnScaleFactor(1.5));
	EXPECT_CALL(events, OnSourceFile("From.bmp"));
	EXPECT_CALL(events, OnDestinationFile("To.bmp"));

	parser.Process({"-scale", "1.5", "-src", "From.bmp", "-dest", "To.bmp"});
}

TEST_F(TestParseCmdLine, Process_MultipleSameCommands_EventMultipleCalled)
{
	testing::InSequence order;
	EXPECT_CALL(events, OnScaleFactor(1.5));
	EXPECT_CALL(events, OnScaleFactor(2.75));
	EXPECT_CALL(events, OnScaleFactor(0.25));

	parser.Process({"-scale", "1.5", "-scale", "2.75", "-scale", "0.25"});
}
