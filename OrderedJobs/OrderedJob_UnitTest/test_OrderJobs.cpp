#include "gtest/gtest.h"
#include "OrderJobs.h"
#include "Exceptions.h"

TEST(TestOrderedJobs, Sort_RegisterTwoIndependent_ReturnJobsOrdered)
{
	OrderJobs::OrderedJobs oJobs{};

	oJobs.Register('a');
	oJobs.Register('b');
	auto actual = oJobs.Sort();
	auto expect = "ab";

	ASSERT_EQ(actual, expect);
}

TEST(TestOrderedJobs, Sort_RegisterOneJob_ReturnTwoJobsOrdered)
{
	OrderJobs::OrderedJobs oJobs{};

	oJobs.Register('b', 'c');
	auto actual = oJobs.Sort();
	auto expect = "cb";

	ASSERT_EQ(actual, expect);
}

TEST(TestOrderedJobs, Sort_RegisterOneJobAndChangeDependency_ReturnTwoJobsOrdered)
{
	OrderJobs::OrderedJobs oJobs{};

	oJobs.Register('b', 'c');
	oJobs.Register('b');
	auto actual = oJobs.Sort();
	auto expect = "bc";

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
	oJobs.Register('d', 'c');
	oJobs.Register('c', 'b');
	oJobs.Register('b', 'a');
	auto actual = oJobs.Sort();
	auto expect = "abcd";

	ASSERT_EQ(actual, expect);
}

TEST(TestOrderedJobs, Sort_DirectCircularDependency_ReturnException)
{
	OrderJobs::OrderedJobs oJobs{};
	EXPECT_THROW(
		{
			oJobs.Register('a', 'b');
			oJobs.Register('c', 'a');
			oJobs.Register('b', 'a');
			auto actual = oJobs.Sort();
		}, DirectCircularDependencyException
	);
}

TEST(TestOrderedJobs, Sort_IndirectCircularDependency_ReturnException)
{
	OrderJobs::OrderedJobs oJobs{};
	EXPECT_THROW(
		{
			oJobs.Register('a', 'b');
			oJobs.Register('b', 'c');
			oJobs.Register('c', 'a');
			auto actual = oJobs.Sort();
		}, IndirectCircularDependencyException
	);
}