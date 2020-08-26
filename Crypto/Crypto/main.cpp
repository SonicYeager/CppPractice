#include "Crypto.h"
#include <iostream>

int main(int argc, const char* argv[])
{
	const char* args[] = {"2", "5", "Crypted.txt"};
	ErrorCode err = Crypto::Run(3, args);

	//const char* args[] = {"2", "5", "Text.txt"};
	//ErrorCode err = Crypto::Run(3, args);

	//const char* args[] = {"2", "5", ""};
	//ErrorCode err = Crypto::Run(3, args);

	//ErrorCode err = Crypto::Run(argc - 1, argv + 1);
	return err == SUCCESS ? 0 : -err;
}
