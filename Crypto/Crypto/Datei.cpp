#include "Datei.h"

auto Datei::GetFile() -> FILE *
{
	return this->mp_file;
}
