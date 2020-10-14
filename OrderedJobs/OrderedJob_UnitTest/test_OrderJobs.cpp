#include "gtest/gtest.h"
#include "OrderJobs.h"

TEST(TestOrderedJobs, Sort_RegisterIndependent_ReturnJobsUnordered)
{
	OrderJobs::OrderedJobs oJobs{};

	oJobs.Register('a');
	oJobs.Register('b');
	oJobs.Register('c');
	oJobs.Register('d');
	auto actual = oJobs.Sort();
	auto expect = "abcd";

	ASSERT_EQ(actual, expect);
}

TEST(TestOrderedJobs, Sort_RegisterOneDependentAndIndependent_ReturnJobsOrderedByDependentIndependent)
{
	OrderJobs::OrderedJobs oJobs{};

	oJobs.Register('b', 'c');
	oJobs.Register('c');
	auto actual = oJobs.Sort();
	auto expect = "cb";

	ASSERT_EQ(actual, expect);
}

TEST(TestOrderedJobs, Sort_RegisterTwoDependentAndOneIndependent_ReturnJobsOrderedByDependency)
{
	OrderJobs::OrderedJobs oJobs{};

	oJobs.Register('c');
	oJobs.Register('b', 'c');
	oJobs.Register('a', 'c');
	auto actual = oJobs.Sort();
	auto expect = "cab";

	ASSERT_EQ(actual, expect);
}

TEST(TestOrderedJobs, Sort_DependencyChain_ReturnJobsOrderedByDependency)
{
	OrderJobs::OrderedJobs oJobs{};

	oJobs.Register('c');
	oJobs.Register('c', 'b');
	oJobs.Register('b', 'a');
	auto actual = oJobs.Sort();
	auto expect = "abc";

	ASSERT_EQ(actual, expect);
}