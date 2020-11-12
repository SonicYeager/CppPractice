#include "gmock/gmock.h"
#include "InMemoryDirectory.h"
#include <memory>

bool operator==(const Element& left, const Element& right)
{
	return left.GetName() == right.GetName() && left.GetText() == right.GetText();
}


TEST(TestInMemoryDirectory, AddElement_AddOne_Heinz)
{
	InMemoryDirectory imd{};

	imd.AddElement(std::make_unique<Element>("Heinz"));

	auto actual = imd.GetElement("Heinz");
	auto expected = Element("Heinz");
	EXPECT_EQ(*actual, expected);
}

TEST(TestInMemoryDirectory, AddElement_AddMultiple_NoIndex)
{
	InMemoryDirectory imd{};

	imd.AddElement(std::make_unique<Element>("Heinz"));
	imd.AddElement(std::make_unique<Element>("Karl"));
	imd.AddElement(std::make_unique<Element>("Gustav"));

	auto actual = imd.GetElement("index");
	EXPECT_EQ(actual, nullptr);
}

TEST(TestInMemoryDirectory, AddElement_AddMultipleWithGenerateIndexBefore_UpdateIndex)
{
	InMemoryDirectory imd{};
	imd.GenerateIndex();

	imd.AddElement(std::make_unique<Element>("Heinz"));
	imd.AddElement(std::make_unique<Element>("Karl"));
	imd.AddElement(std::make_unique<Element>("Gustav"));

	auto actual = imd.GetElement("index")->GetText();
	auto expected = "Heinz\nKarl\nGustav\n";
	EXPECT_EQ(actual, expected);
	auto actualCount = imd.GetElementCount();
	EXPECT_EQ(actualCount, 4);
}

TEST(TestInMemoryDirectory, GenerateIndex_OneTimes_CorrectIndex)
{
	InMemoryDirectory imd{};

	imd.AddElement(std::make_unique<Element>("Fury"));
	imd.AddElement(std::make_unique<Element>("Tony"));
	imd.AddElement(std::make_unique<Element>("Bruce"));
	imd.GenerateIndex();

	auto actual = imd.GetElement("index")->GetText();
	auto expected = "Fury\nTony\nBruce\n";
	EXPECT_EQ(actual, expected);
	auto actualCount = imd.GetElementCount();
	EXPECT_EQ(actualCount, 4);
}

TEST(TestInMemoryDirectory, GenerateIndex_MultipleTimesWithAddBetween_JustOneIndex)
{
	InMemoryDirectory imd{};

	imd.GenerateIndex();
	imd.AddElement(std::make_unique<Element>("Heinz"));
	imd.AddElement(std::make_unique<Element>("Knut"));
	imd.AddElement(std::make_unique<Element>("Chester"));
	imd.GenerateIndex();

	auto actual = imd.GetElement("index")->GetText();
	auto expected = "Heinz\nKnut\nChester\n";
	EXPECT_EQ(actual, expected);
	auto actualCount = imd.GetElementCount();
	EXPECT_EQ(actualCount, 4);
}

TEST(TestInMemoryDirectory, GenerateIndex_MultipleTimes_JustOneIndex)
{
	InMemoryDirectory imd{};

	imd.AddElement(std::make_unique<Element>("Heinz"));
	imd.GenerateIndex();
	imd.GenerateIndex();

	auto actual = imd.GetElement("index")->GetText();
	auto expected = "Heinz\n";
	EXPECT_EQ(actual, expected);
	auto actualCount = imd.GetElementCount();
	EXPECT_EQ(actualCount, 2);
}