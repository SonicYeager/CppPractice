#include "Title.h"

Title::Title(std::chrono::milliseconds start, std::chrono::milliseconds length, std::string txt, int size)
	: Clip{start, length}
	, text(txt)
	, pointSize(size)
{}

void Title::Visit(IOperations* visitor)
{
	visitor->PerformOn(this->shared_from_this()); //Visitor
}
