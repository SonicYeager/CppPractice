#include "gmock/gmock.h"
#include "ProductCode.h"

struct StubReader : IReader
{
	StubReader()
	{
		ON_CALL(*this, CheckFile(::testing::_)).WillByDefault(::testing::Return(true));
		ON_CALL(*this, IsExtensionSupported(::testing::_)).WillByDefault(::testing::Return(true));
		ON_CALL(*this, IsLoaded()).WillByDefault(::testing::Return(true));
	}
	MOCK_METHOD(bool, CheckFile, (const std::wstring& filePath), (override));
	MOCK_METHOD(bool, IsExtensionSupported, (const std::wstring& extension), (override));
	MOCK_METHOD(bool, IsLoaded, (), (override));
};

struct FileCheckerUnderTest : FileChecker
{
	std::unique_ptr<IReader> CreateReader() override
	{
		return std::make_unique<::testing::NiceMock<StubReader>>();
	}
};

TEST(TestFileChecker, Check_ValidPathWithSlash_ReturnTrue)
{
	FileCheckerUnderTest fc;
	std::wstring path{ L"TestData/Testy.txt" };

	auto actual = fc.Check(path);

	EXPECT_TRUE(actual);
}

TEST(TestFileChecker, Check_ValidPathWithBackslash_ReturnTrue)
{
	FileCheckerUnderTest fc;
	std::wstring path{ L"TestData\\Testy.txt" };

	auto actual = fc.Check(path);

	EXPECT_TRUE(actual);
}

TEST(TestFileChecker, Check_InvalidPathNoExtension_ReturnFalse)
{
	FileCheckerUnderTest fc;
	std::wstring path{ L"TestData/Testy" };

	auto actual = fc.Check(path);

	EXPECT_FALSE(actual);
}

TEST(TestFileChecker, Check_InvalidPathNoFilename_ReturnFalse)
{
	FileCheckerUnderTest fc;
	std::wstring path{ L"TestData/.txt" };

	auto actual = fc.Check(path);

	EXPECT_FALSE(actual);
}

TEST(TestFileChecker, Check_InvalidPathNoExtensionNoFilename_ReturnFalse)
{
	FileCheckerUnderTest fc;
	std::wstring path{ L"TestData/" };

	auto actual = fc.Check(path);

	EXPECT_FALSE(actual);
}