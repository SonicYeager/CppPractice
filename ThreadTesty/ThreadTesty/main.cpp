#include <iostream>
#include <future>

long fib(long n)
{
	return n <= 1 ? n : fib(n - 1) + fib(n - 2);
}

int main() {
	while (true) {
		auto f40 = std::async(fib, 40);
		auto f41 = std::async(fib, 41);
		auto f42 = std::async(fib, 42);
		auto f43 = std::async(fib, 43);
		auto f44 = std::async(fib, 44);
		auto f45 = std::async(fib, 45);
		auto f46 = std::async(fib, 46);
		auto f47 = std::async(fib, 47);
		auto f48 = std::async(fib, 48);
		auto f49 = std::async(fib, 49);
		auto f50 = std::async(fib, 50);
		auto f51 = std::async(fib, 51);
		auto f52 = std::async(fib, 52);
		auto f53 = std::async(fib, 53);
		auto f54 = std::async(fib, 54);
		auto f56 = std::async(fib, 56);

		std::cout << "fib(40): " << f40.get() << std::endl;
		std::cout << "fib(41): " << f41.get() << std::endl;
		std::cout << "fib(42): " << f42.get() << std::endl;
		std::cout << "fib(43): " << f43.get() << std::endl;
		std::cout << "fib(44): " << f44.get() << std::endl;
		std::cout << "fib(45): " << f45.get() << std::endl;
		std::cout << "fib(46): " << f46.get() << std::endl;
		std::cout << "fib(47): " << f47.get() << std::endl;
		std::cout << "fib(48): " << f48.get() << std::endl;
		std::cout << "fib(49): " << f49.get() << std::endl;
		std::cout << "fib(50): " << f50.get() << std::endl;
		std::cout << "fib(51): " << f51.get() << std::endl;
		std::cout << "fib(52): " << f52.get() << std::endl;
		std::cout << "fib(53): " << f53.get() << std::endl;
		std::cout << "fib(54): " << f54.get() << std::endl;
		std::cout << "fib(56): " << f56.get() << std::endl;
	}
}