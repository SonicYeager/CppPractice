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
	oJobs.Register('a', 'b');
	EXPECT_THROW(oJobs.Register('b', 'a'), DirectCircularDependencyException);
}

TEST(TestOrderedJobs, Sort_IndirectCircularDependencyWithoutIndependent_ReturnException)
{
	OrderJobs::OrderedJobs oJobs{};
	oJobs.Register('a', 'b');
	oJobs.Register('b', 'c');

	EXPECT_THROW(oJobs.Register('c', 'a'), IndirectCircularDependencyException);
}

TEST(TestOrderedJobs, Sort_IndirectCircularDependencyWithIndependent_ReturnException)
{
	OrderJobs::OrderedJobs oJobs{};
	EXPECT_THROW(
		{
			oJobs.Register('a');
			oJobs.Register('b', 'c');
			oJobs.Register('c', 'd');
			oJobs.Register('d', 'b');
			oJobs.Register('e', 'a');
			oJobs.Sort();
		}, IndirectCircularDependencyException
	);
}

TEST(TestOrderedJobs, Sort_DirectCircularDependencyOnSelf_ReturnException)
{
	OrderJobs::OrderedJobs oJobs{};
	EXPECT_THROW(
		oJobs.Register('a', 'a'), DirectCircularDependencyException
	);
}