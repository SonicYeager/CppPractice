#include "gmock/gmock.h"
#include "ProductCode.h"

class StubReader : public Reader
{
public:
	MOCK_METHOD(void, SetLib, (const HMODULE&), (override));
	MOCK_METHOD(bool, CheckFile, (const std::wstring&), (override));
	MOCK_METHOD(bool, IsExtensionSupported, (const std::wstring&), (override));
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


TEST(TestFileChecker, Check_ValidPath_ReturnTrue)
{
	FileChecker fc{};
	const std::wstring path{ L"C:\\tmp\\HelloWorld.txt" };

	auto actual = fc.Check(path);

	EXPECT_TRUE(actual); 
}

TEST(TestFileChecker, Check_InvalidPath_ReturnFalse)
{
	FileChecker fc{};
	const std::wstring path{ L"C:/tmp/HelloWorld.txt" };

	auto actual = fc.Check(path);

	EXPECT_TRUE(actual);
}