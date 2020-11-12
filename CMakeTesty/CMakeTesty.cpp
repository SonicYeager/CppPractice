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
		return 1;
	}
	return 0;
}
