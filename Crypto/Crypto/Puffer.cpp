#include "Puffer.h"

auto Puffer::GetChar() -> char *
{
	return this->mp_var;
}

auto Puffer::SetChar() -> char*&
{
	return this->mp_var;
}
