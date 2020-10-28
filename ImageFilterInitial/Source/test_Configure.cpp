#include <gmock/gmock.h>
#include "Configure.h"

#pragma region Prepare
class ConfigureEventFake
{
public:
	MOCK_METHOD3(OnValid, void(const std::string&, const std::string&, const FilterAlgorithm&));
};

class TestConfigure : public testing::Test
{
public:
	TestConfigure()
	{
		config.onValid = [this](const std::string& src, const std::string& dest, const FilterAlgorithm& alg) {
			events.OnValid(src, dest, alg);
		};
	}
	Configure config;
	testing::StrictMock<ConfigureEventFake> events;
};
#pragma endregion


TEST_F(TestConfigure, Validate_ValidConfig_CallOnValid)
{
	config.SetSourceFilePath("Test.bmp");
	config.SetDestinationFilePath("Result.bmp");

	EXPECT_CALL(events, OnValid("Test.bmp", "Result.bmp", testing::_));

	auto ret = config.Validate();

	EXPECT_EQ(0, ret);
}

TEST_F(TestConfigure, Validate_ValidConfigWithoutDestPathSet_CallOnValid)
{
	config.SetSourceFilePath("Test.bmp");

	EXPECT_CALL(events, OnValid("Test.bmp", "TestResult.bmp", testing::_));

	auto ret = config.Validate();

	EXPECT_EQ(0, ret);
}

TEST_F(TestConfigure, Validate_InValidConfig_CallNothing)
{
	config.SetDestinationFilePath("Test.bmp");

	EXPECT_CALL(events, OnValid(testing::_, testing::_, testing::_)).Times(0);

	auto ret = config.Validate();

	EXPECT_EQ(-1, ret);
}
