#include "gmock/gmock.h"
#include "ProductCode.h"

class StubReader : public LegacyReader
{
public:
	MOCK_METHOD(void, SetLib, (const std::string&), (override));
	bool CheckFile(const std::filesystem::path&) override
	{
		return true;
	}
	bool IsExtensionSupported(const std::filesystem::path&) override
	{
		return true;
	}
};

class MockFileChecker : public FileChecker
{
	private:
		std::unique_ptr<LegacyReader> CreateReader() override
		{
			return std::make_unique<StubReader>();
		}
};


TEST(TestFileChecker, Check_ValidPathWithDash_ReturnTrue)
{
	::testing::StrictMock<MockFileChecker> fc;
	std::wstring path{ L"C:/Uebungsprojekte/FileCheckerTested/Testy.txt" };

	auto actual = fc.Check(path);

	EXPECT_TRUE(actual);
}

TEST(TestFileChecker, Check_ValidPathWithCounterDashes_ReturnTrue)
{
	::testing::StrictMock<MockFileChecker> fc;
	std::wstring path{ L"C:\\Uebungsprojekte\\FileCheckerTested\\Testy.txt" };

	auto actual = fc.Check(path);

	EXPECT_TRUE(actual);
}

TEST(TestFileChecker, Check_InvalidPathNoExtension_ReturnFalse)
{
	::testing::StrictMock<MockFileChecker> fc;
	std::wstring path{ L"C:\\Uebungsprojekte\\FileCheckerTested\\Testy" };

	auto actual = fc.Check(path);

	EXPECT_FALSE(actual);
}

TEST(TestFileChecker, Check_InvalidPathNoFilename_ReturnTrue)
{
	::testing::StrictMock<MockFileChecker> fc;
	std::wstring path{ L"C:\\Uebungsprojekte\\FileCheckerTested\\.txt" };

	auto actual = fc.Check(path);

	EXPECT_FALSE(actual);
}

TEST(TestFileChecker, Check_InvalidPathNoFilenameNoExtension_ReturnTrue)
{
	::testing::StrictMock<MockFileChecker> fc;
	std::wstring path{ L"C:\\Uebungsprojekte\\FileCheckerTested\\" };

	auto actual = fc.Check(path);

	EXPECT_FALSE(actual);
}

TEST(TestFileChecker, Check_InvalidPathEmpty_ReturnTrue)
{
	::testing::StrictMock<MockFileChecker> fc;
	std::wstring path{ L"" };

	auto actual = fc.Check(path);

	EXPECT_FALSE(actual);
}