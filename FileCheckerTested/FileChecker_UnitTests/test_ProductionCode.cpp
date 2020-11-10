#include "gmock/gmock.h"
#include "ProductCode.h"

class StubReader : public LegacyReader
{
public:
	MOCK_METHOD(void, SetLib, (const std::string&), (override));
	bool CheckFile(const std::wstring&) override
	{
		return true;
	}
	bool IsExtensionSupported(const std::wstring&) override
	{
		return true;
	}
};

//TEST(TestFileChecker, Check_ValidPath_ReturnTrue)
//{
//	FileChecker fc;
//	std::wstring path{ L"C:\\Uebungsprojekte\\FileCheckerTested\\Testy.txt" };
//
//	auto actual = fc.Check(path);
//
//	EXPECT_TRUE(actual);
//}