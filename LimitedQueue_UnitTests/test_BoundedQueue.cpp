#include "gtest/gtest.h"
#include "BoundedQueue.h"
#include <future>


TEST(TestBoundedQueue, Enqueue_OneEnqueueViaOneThread_SetOneEntryInQueue)
{
	Bounded::BoundedQueue<int> queue{};

	auto as = std::async(std::launch::async, std::bind(&Bounded::BoundedQueue<int>::Enqueue, &queue, 2));
	as.get();

	auto actual = queue.Size();
	auto expect = 1;
	EXPECT_EQ(queue.Size(), expect);
}

TEST(TestBoundedQueue, Dequeue_OneEnqueueOneDequeue_ReturnQueuedEntry)
{
	Bounded::BoundedQueue<int> queue{};

	auto writingThread = std::async(std::launch::async, std::bind(&Bounded::BoundedQueue<int>::Enqueue, &queue, 2));
	auto readingThread = std::async(std::launch::async, std::bind(&Bounded::BoundedQueue<int>::Dequeue, &queue));

	auto actual = readingThread.get();
	auto expect = 2;
	EXPECT_EQ(actual, expect);
}

TEST(TestBoundedQueue, Enqueue_EnqueueOnFullQueue_ThreadBlocked)
{
	Bounded::BoundedQueue<int> queue{};

	auto as1 = std::async(std::launch::async, std::bind(&Bounded::BoundedQueue<int>::Enqueue, &queue, 2));
	auto as2 = std::async(std::launch::async, std::bind(&Bounded::BoundedQueue<int>::Enqueue, &queue, 3));
	auto as3 = std::async(std::launch::async, std::bind(&Bounded::BoundedQueue<int>::Enqueue, &queue, 4));
	as1.get();
	as2.get();

	auto actual = queue.Size();
	auto expect = 2;
	EXPECT_EQ(actual, expect);

	auto as = std::async(std::launch::async, std::bind(&Bounded::BoundedQueue<int>::Dequeue, &queue));
	auto s = as.get();
	as3.get();

	actual = queue.Size();
	expect = 2;
	EXPECT_EQ(actual, expect);
}

TEST(TestBoundedQueue, Dequeue_DequeueOnEmptyQueue_ThreadBlocked)
{
	Bounded::BoundedQueue<int> queue{};

	auto as = std::async(std::launch::async, std::bind(&Bounded::BoundedQueue<int>::Dequeue, &queue));

	auto actual = queue.Size();
	auto expect = 0;
	EXPECT_EQ(actual, expect);

	auto as2 = std::async(std::launch::async, std::bind(&Bounded::BoundedQueue<int>::Enqueue, &queue, 3));

	actual = as.get();
	expect = 3;
	EXPECT_EQ(actual, expect);
}