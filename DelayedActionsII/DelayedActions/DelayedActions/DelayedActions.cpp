#include <iostream>
#include "LazyMemory.h"

int main()
{
	LazyMemory lazyMem;
	for(int i = 0; i < 5; i++)
	{
		lazyMem.PushBack(i);
		lazyMem.PushFront(i * 10);
	}
	lazyMem.Display();
	lazyMem.Sort();
	lazyMem.Display();
	std::cout << lazyMem.Size() << std::endl;

	LazyMemory lazyMemII(1);
	for(int i = 0; i < 5; i++)
	{
		lazyMemII.PushBack(i);
		lazyMemII.PushFront(i * 10);
	}
	lazyMemII.PushFront(20);
	lazyMemII.Sort();
	lazyMemII.Display();
	std::cout << lazyMemII.Size() << std::endl;
	lazyMemII.Erase(2);
	lazyMemII.Erase(20);
	lazyMemII.Erase(2000);
	lazyMemII.Display();
	std::cout << lazyMemII.Size() << std::endl;
	lazyMemII.Clear();
	std::cout << lazyMemII.IsEmpty() << std::endl;
	std::cin.get();
}
