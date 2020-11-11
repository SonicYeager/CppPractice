#include "gmock/gmock.h"
#include "InMemoryDirectory.h"
#include <memory>

TEST(TestInMemoryDirectory, AddElement_AddOneElement_OneElementAndOneIndexWithTextOfOneElement)
{
	InMemoryDirectory imd{};

	imd.AddElement(std::make_unique<Element>("Heinz"));

	auto actual = imd.GetElement("Heinz");
	auto expected = Element("Heinz");
	EXPECT_EQ(*actual, expected);
}

TEST(TestInMemoryDirectory, GenerateIndex_AddOneElement_OneIndexWithCorrectText)
{
	InMemoryDirectory imd{};

	imd.AddElement(std::make_unique<Element>("Heinz"));
	imd.GenerateIndex();

	auto index = imd.GetElement("index");
	auto actual = index->GetText();
	auto expected = "Index\nHeinz\n";
	EXPECT_EQ(actual, expected);
}

TEST(TestInMemoryDirectory, GenerateIndex_AddMultipleElement_OneIndexWithCorrectText)
{
	InMemoryDirectory imd{};

	imd.AddElement(std::make_unique<Element>("Heinz"));
	imd.AddElement(std::make_unique<Element>("Kunz"));
	imd.AddElement(std::make_unique<Element>("Donald"));
	imd.AddElement(std::make_unique<Element>("Biden"));
	imd.GenerateIndex();

	auto index = imd.GetElement("index");
	auto actual = index->GetText();
	auto expected = "Index\nHeinz\nKunz\nDonald\nBiden\n";
	EXPECT_EQ(actual, expected);
}