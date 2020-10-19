#pragma once
#include <queue>
#include <mutex>
#include <shared_mutex>
#include <condition_variable>
#include <chrono>

using namespace std::chrono_literals;

namespace Bounded
{
	//DECLARATION
	template<typename Type>
	struct BoundedQueue
	{
		explicit BoundedQueue(size_t maxSize = 2) noexcept;
		bool TryEnqueue(Type element, std::chrono::milliseconds maxWait);
		bool TryDequeue(Type* element, std::chrono::milliseconds maxWait);
		void Enqueue(Type element);
		Type Dequeue();
		size_t Size() const;
		size_t maxSize{};
	private:
		std::mutex mutx;
		std::condition_variable_any condition{};
		std::queue<Type> queue{};
	};


	//IMPLEMENTATION
	template<typename Type>
	BoundedQueue<Type>::BoundedQueue(size_t maxSize) noexcept : maxSize(maxSize)
	{}

	template<typename Type>
	void BoundedQueue<Type>::Enqueue(Type element)
	{
		std::unique_lock<std::mutex> lk(mutx);
		condition.wait(lk, [&] {return Size() < maxSize; });
		queue.push(element);
		lk.unlock();
		condition.notify_all();
	}

	template<typename Type>
	Type BoundedQueue<Type>::Dequeue()
	{
		std::unique_lock<std::mutex> lk(mutx);
		condition.wait(lk, [&] {return Size() > 0; });
		auto res = queue.front();
		queue.pop();
		lk.unlock();
		condition.notify_all();
		return res;
	}

	template<typename Type>
	bool BoundedQueue<Type>::TryEnqueue(Type element, std::chrono::milliseconds maxWait)
	{
		std::unique_lock<std::mutex> lk(mutx);
		bool wait = condition.wait_for(lk, maxWait, [&] {return Size() < maxSize; });
		if (wait)
		{
			queue.push(element);
			lk.unlock();
			condition.notify_all();
			return true;
		}
		else
			return false;
	}

	template<typename Type>
	bool BoundedQueue<Type>::TryDequeue(Type* element, std::chrono::milliseconds maxWait)
	{
		std::unique_lock<std::mutex> lk(mutx);
		bool wait = condition.wait_for(lk, maxWait, [&] {return Size() > 0; });
		if (wait)
		{
			*element = queue.front();
			queue.pop();
			lk.unlock();
			condition.notify_all();
			return true;
		}
		else
			return false;
	}

	template<typename Type>
	size_t BoundedQueue<Type>::Size() const
	{
		return this->queue.size();
	}
}

