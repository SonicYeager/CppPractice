#include "gtest/gtest.h"
#include "BoundedQueue.h"
#include <future>


TEST(TestBoundedQueue, Enqueue_OneEnqueue_SetOneEntryInQueue)
{
	Bounded::BoundedQueue<int> queue{};

	auto as = std::async(std::launch::async, std::bind(&Bounded::BoundedQueue<int>::Enqueue, &queue, 2));
	as.get();

	const auto actual = queue.Size();
	constexpr auto expect = 1;
	EXPECT_EQ(queue.Size(), expect);
}

TEST(TestBoundedQueue, Dequeue_OneEnqueueOneDequeue_ReturnQueuedEntry)
{
	Bounded::BoundedQueue<int> queue{};

	auto writingThread = std::async(std::launch::async, std::bind(&Bounded::BoundedQueue<int>::Enqueue, &queue, 2));
	auto readingThread = std::async(std::launch::async, std::bind(&Bounded::BoundedQueue<int>::Dequeue, &queue));

	auto actual = readingThread.get();
	constexpr auto expect = 2;
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

	queue.Dequeue();
	as3.get();
}

TEST(TestBoundedQueue, Dequeue_DequeueOnEmptyQueue_ThreadBlocked)
{
	Bounded::BoundedQueue<int> queue{};

	auto as = std::async(std::launch::async, std::bind(&Bounded::BoundedQueue<int>::Dequeue, &queue));

	auto actual = queue.Size();
	auto expect = 0;
	EXPECT_EQ(actual, expect);

	queue.Enqueue(1);
	as.get();
}

TEST(TestBoundedQueue, Dequeue_ManyEntrys_ReturnCorrectValue)
{
	Bounded::BoundedQueue<int> queue{5};
	std::vector<std::future<int>> rthreads{};
	std::vector<std::future<void>> wthreads{};

	for (size_t i = 0; i < 10; ++i)
	{
		wthreads.push_back(std::async(std::launch::async, std::bind(&Bounded::BoundedQueue<int>::Enqueue, &queue, i)));
	}
	for (size_t i = 0; i < 10; i++)
	{
		rthreads.push_back(std::async(std::launch::async, std::bind(&Bounded::BoundedQueue<int>::Dequeue, &queue)));
	}
	int sum{};
	for (auto& th : rthreads)
		sum += th.get();

	const auto actual = sum;
	constexpr auto expect = 45;
	EXPECT_EQ(actual, expect);
}

TEST(TestBoundedQueue, TryEnqueue_BlockedBeyondMaxWaitTime_ReturnFalseQueueEmpty)
{
	Bounded::BoundedQueue<int> queue{ 1 };
	queue.Enqueue(2);
	auto call = [&queue]
	{
		std::this_thread::sleep_for(13ms);
		queue.Dequeue();
	};
	auto as = std::async(std::launch::async, call);

	auto actual = queue.TryEnqueue(2, 10ms);

	EXPECT_FALSE(actual);
	as.get();
}

TEST(TestBoundedQueue, TryDequeue_BlockedBeyondMaxWaitTime_ReturnFalseNullPtr)
{
	Bounded::BoundedQueue<int> queue{ 1 };
	int actualVal{};
	auto call = [&queue]
	{
		std::this_thread::sleep_for(11ms);
		queue.Enqueue(2);
	};
	auto th = std::async(std::launch::async, call);

	auto actual = queue.TryDequeue(&actualVal, 10ms);

	EXPECT_FALSE(actual);
	auto expect = 0;
	EXPECT_EQ(actualVal, expect);
}

TEST(TestBoundedQueue, TryEnqueue_BlockedAndFreeWithinMaxWaitTime_ReturnTrueAndOneEntryInQueue)
{
	Bounded::BoundedQueue<int> queue{ 1 };

	queue.Enqueue(2);

	auto th = std::async(std::launch::async, std::bind(&Bounded::BoundedQueue<int>::TryEnqueue, &queue, 2, 100ms));
	std::this_thread::sleep_for(30ms);
	queue.Dequeue();
	auto actual = th.get();
	auto expect = true;
	EXPECT_EQ(actual, expect);
}

TEST(TestBoundedQueue, TryDequeue_BlockedAndFreeWithinMaxWait_ReturnTrueAndSetRet2)
{
	Bounded::BoundedQueue<int> queue{ 1 };

	int actual{};
	auto th = std::async(std::launch::async, std::bind(&Bounded::BoundedQueue<int>::TryDequeue, &queue, &actual, 100ms));
	std::this_thread::sleep_for(30ms);
	queue.Enqueue(2);
	th.get();
	auto expect = 2;
	EXPECT_EQ(actual, expect);
}