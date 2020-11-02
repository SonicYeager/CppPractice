#include "InternalTypes.h"
#include "FileHandler.h"

int main()
{
	TOOLBOX::FILE::WRITER::LinesWriter lw;
	TOOLBOX::FILE::READER::LinesReader lr;
	TOOLBOX::FILE::File<TOOLBOX::Lines> lfile{lr, lw};
	TOOLBOX::Lines text = lfile.Read("Shit.txt");

	TOOLBOX::FILE::READER::ObjectReader<TOOLBOX::Dummy> oreader;
	TOOLBOX::FILE::WRITER::ObjectWriter<TOOLBOX::Dummy> owriter;
	TOOLBOX::FILE::File<TOOLBOX::Dummy> ofile{ oreader, owriter };
}