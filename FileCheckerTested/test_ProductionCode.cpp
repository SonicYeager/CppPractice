#include "gmock/gmock.h"
#include "ProductCode.h"

class StubReader : public Reader
{
public:
	MOCK_METHOD(void, SetLib, (const HMODULE&), (override));
	//MOCK_METHOD(bool, CheckFile, (const std::wstring&), (override));
	//MOCK_METHOD(bool, IsExtensionSupported, (const std::wstring&), (override));
	bool CheckFile(const std::wstring&) override
	{
		return true;
	}
	bool IsExtensionSupported(const std::wstring&) override
	{
		return true;
	}
};

class MockFileChecker : public FileChecker
{
public:
	using FileChecker::Check;

protected:
	virtual void CreateReader() override
	{
		reader = std::make_unique<StubReader>();
	}
};


TEST(TestFileChecker, Check_ValidPathWithDash_ReturnFalse)
{
	::testing::StrictMock<MockFileChecker> fc{};
	const std::wstring path{ L"C:/Uebungsprojekte/FileCheckerTested/FALCON.BMP" };

	auto actual = fc.Check(path);

	EXPECT_TRUE(actual);
}

TEST(TestFileChecker, Check_ValidPath_ReturnTrue)
{
	::testing::StrictMock<MockFileChecker> fc{};
	const std::wstring path{ L"C:\\Uebungsprojekte\\FileCheckerTested\\FALCON.BMP" };

	auto actual = fc.Check(path);

	EXPECT_TRUE(actual); 
}

TEST(TestFileChecker, Check_InvalidPathNoExtension_ReturnFalse)
{
	::testing::StrictMock<MockFileChecker> fc{};
	const std::wstring path{ L"C:\\Uebungsprojekte\\FileCheckerTested\\FALCON" };

	auto actual = fc.Check(path);

	EXPECT_FALSE(actual);
}

TEST(TestFileChecker, Check_InvalidPathNoFileNameWithExtension_ReturnFalse)
{
	::testing::StrictMock<MockFileChecker> fc{};
	const std::wstring path{ L"C:\\Uebungsprojekte\\FileCheckerTested\\.BMP" };

	auto actual = fc.Check(path);

	EXPECT_FALSE(actual);
}

TEST(TestFileChecker, Check_InvalidPathNoFileNameNoExtension_ReturnFalse)
{
	::testing::StrictMock<MockFileChecker> fc{};
	const std::wstring path{ L"C:\\Uebungsprojekte\\FileCheckerTested\\" };

	auto actual = fc.Check(path);

	EXPECT_FALSE(actual);
}

TEST(TestFileChecker, Check_InvalidPathEmpty_ReturnFalse)
{
	::testing::StrictMock<MockFileChecker> fc{};
	const std::wstring path{ L"" };

	auto actual = fc.Check(path);

	EXPECT_FALSE(actual);
}