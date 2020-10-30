#include "InternalTypes.h"
#include "FileHandler.h"

int main()
{
	TOOLBOX::FILE::WRITER::LinesWriter lw;
	TOOLBOX::FILE::READER::LinesReader lr;
	TOOLBOX::FILE::File<TOOLBOX::Lines> file{lr, lw};
	TOOLBOX::Lines text = file.Read("Shit.txt");
}