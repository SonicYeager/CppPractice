//#include <string>
#include <assert.h>
#include "Crypt.h"

void main() 
{
	auto result = EncryptROTXIII("Dies hier wird mit ROT-13 verschlüsselt.");
	assert(result == "QVRF UVRE JVEQ ZVG EBG-13 IREFPUYHRFFRYG.");
	result = EncryptROTXIII("Hellö, World");
	assert(result == "URYYBR, JBEYQ");
	result = EncryptROTXIII("Äöüß**_!#");
	assert(result == "NRBRHRFF**_!#");
}