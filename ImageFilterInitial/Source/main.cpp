#include "ProcessImage.h"

int main(int argc, char* argv[])
{
	// First command line argument is the .exe -> skip first element
	return ProcessImage::Run({argv + 1, argv + argc});
}
