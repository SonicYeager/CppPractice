#include "Crypto.h"
#include <iostream>

auto main(int argc, const char* argv[]) -> int
{
	const char* args[] = {"2", "5", "Crypted.txt"};
	Crypto::Run(3, args);

	//const char* args[] = {"2", "5", "Text.txt"};
	//ErrorCode err = Crypto::Run(3, args);

	//const char* args[] = {"2", "5", ""};
	//ErrorCode err = Crypto::Run(3, args);

	//ErrorCode err = Crypto::Run(argc - 1, argv + 1);
	return 0;
}
