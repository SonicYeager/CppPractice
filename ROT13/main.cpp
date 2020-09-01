//#include <string>
#include <assert.h>
#include "Crypt.h"

void main() 
{
	auto result = EncryptROTXIII("Dies hier wird mit ROT-13 verschlüsselt.");
	assert(result == "QVRF UVRE JVEQ ZVG EBG IREFPUYHRFFRYG");
	result = EncryptROTXIII("Hello World");
	assert(result == "URYYB JBEYQ");
}