// CMakeTesty.cpp: Definiert den Einstiegspunkt für die Anwendung.
//

#include "CMakeTesty.h"
#include "Config.h"

int main(int argc, char* argv[])
{
	if (argc < 2) {
		// report version
		std::cout << argv[0] << " Version " << CMakeTesty_VERSION_MAJOR << "."
			<< CMakeTesty_VERSION_MINOR << std::endl;
		std::cout << "Usage: " << argv[0] << " number" << std::endl;
		auto a = std::async(std::launch::async, [] { return 1; });
		return a.get();
		return 1;
	}
	else
	{
		auto a = std::async(std::launch::async, []{ return 0; });
		return a.get();
	}
}
