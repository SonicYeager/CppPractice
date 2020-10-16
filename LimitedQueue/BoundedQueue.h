#pragma once
#include <queue>
#include <mutex>
#include <shared_mutex>
#include <condition_variable>

namespace Bounded 
{
	//loop calling !enq 
	//lock yield lock

	//DECLARATION
	template<typename Type>
	struct BoundedQueue
	{
		explicit BoundedQueue(size_t maxSize = 2);
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
	BoundedQueue<Type>::BoundedQueue(size_t maxSize) : maxSize(maxSize)
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
	size_t BoundedQueue<Type>::Size() const
	{
		return this->queue.size();
	}
}

