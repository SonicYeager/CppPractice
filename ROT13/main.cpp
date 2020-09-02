//#include <string>
#include <assert.h>
#include "Crypt.h"

void main() 
{
	auto result = EncryptROTXIII("Dies hier wird mit ROT-13 verschl�sselt.");
	assert(result == "QVRF UVRE JVEQ ZVG EBG-13 IREFPUYHRFFRYG.");
	result = EncryptROTXIII("Hell�, World");
	assert(result == "URYYBR, JBEYQ");
	result = EncryptROTXIII("����**_!#");
	assert(result == "NRBRHRFF**_!#");
}