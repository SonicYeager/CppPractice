#include "gtest/gtest.h"
#include "gmock/gmock.h"
#include "Logger.h"

class MockWriter : public LOGGER::Writer
{
public:
	MOCK_METHOD(void, Write, (const std::string& txt), (override));
};

TEST(TestLogger, Log_CallOnceWithInfoAndMsg_WriteCalledOnceWithFormattedMsg)
{
	 //Setup
	::testing::StrictMock<MockWriter> stbWriter{};
	LOGGER::Logger log{"Classy", &stbWriter};
	EXPECT_CALL(stbWriter, Write("[INFO]     [Classy]  >>classy<<"));  //prept assert 

	//Execution
	log.Log(LOGGER::PRIORITY::INFO, "classy");
}

TEST(TestLogger, Log_CallOnceWithWarningAndMsg_WriteCalledOnceWithFormattedMsg)
{
	//Setup
	::testing::StrictMock<MockWriter> stbWriter{};
	LOGGER::Logger log{ "Classy", &stbWriter };
	EXPECT_CALL(stbWriter, Write("[WARNING]  [Classy]  >>classy<<"));  //prept assert 

	//Execution
	log.Log(LOGGER::PRIORITY::WARNING, "classy");
}

TEST(TestLogger, Log_CallOnceWithFatalAndMsg_WriteCalledOnceWithFormattedMsg)
{
	//Setup
	::testing::StrictMock<MockWriter> stbWriter{};
	LOGGER::Logger log{ "Classy", &stbWriter };
	EXPECT_CALL(stbWriter, Write("[FATAL]    [Classy]  >>classy<<"));  //prept assert 

	//Execution
	log.Log(LOGGER::PRIORITY::FATAL, "classy");
}

TEST(TestLogger, Log_CallAllThreePrioritysWithMsg_MsgFormat)
{
	//Setup
	::testing::StrictMock<MockWriter> stbWriter{};
	LOGGER::Logger log{ "Classy", &stbWriter };
	::testing::InSequence seq{};
	EXPECT_CALL(stbWriter, Write("[INFO]     [Classy]  >>classy<<"));  //prept assert 
	EXPECT_CALL(stbWriter, Write("[FATAL]    [Classy]  >>classy<<"));  //prept assert
	EXPECT_CALL(stbWriter, Write("[WARNING]  [Classy]  >>classy<<"));  //prept assert

	//Execution
	log.Log(LOGGER::PRIORITY::INFO, "classy");
	log.Log(LOGGER::PRIORITY::FATAL, "classy");
	log.Log(LOGGER::PRIORITY::WARNING, "classy");
}

TEST(TestLogger, Log_WithoutMsg_EmptyMsg)
{
	//Setup
	::testing::StrictMock<MockWriter> stbWriter{};
	LOGGER::Logger log{ "MsgLess", &stbWriter };
	EXPECT_CALL(stbWriter, Write("[INFO]     [MsgLess]"));  //prept assert 

	//Execution
	log.Log(LOGGER::PRIORITY::INFO, "");
}

TEST(TestLogger, Log_DifferentLogger_DifferentLoggerName)
{
	//Setup
	::testing::StrictMock<MockWriter> stbWriter{};
	LOGGER::Logger log{ "Classy", &stbWriter };
	LOGGER::Logger logu{ "Unclassy", &stbWriter };
	EXPECT_CALL(stbWriter, Write("[INFO]     [Classy]  >>classy<<"));  //prept assert 
	EXPECT_CALL(stbWriter, Write("[WARNING]  [Unclassy]  >>classy<<"));  //prept assert
	EXPECT_CALL(stbWriter, Write("[FATAL]    [Classy]  >>classy<<"));  //prept assert

	//Execution
	log.Log(LOGGER::PRIORITY::INFO, "classy");
	logu.Log(LOGGER::PRIORITY::WARNING, "classy");
	log.Log(LOGGER::PRIORITY::FATAL, "classy");
}