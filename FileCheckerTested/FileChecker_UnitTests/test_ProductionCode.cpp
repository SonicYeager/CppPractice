#include "gmock/gmock.h"
#include "ProductCode.h"

TEST(TestFileChecker, Check_ValidPath_ReturnTrue)
{
	FileChecker fc;
	std::wstring path{ L"Testy.txt" };

	auto actual = fc.Check(path);

	EXPECT_TRUE(actual);
}