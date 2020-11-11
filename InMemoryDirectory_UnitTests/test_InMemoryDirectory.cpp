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