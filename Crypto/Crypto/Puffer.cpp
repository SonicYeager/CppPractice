#include "Puffer.h"

char * Puffer::GetChar()
{
	return this->mp_var;
}

char*& Puffer::SetChar()
{
	return this->mp_var;
}
