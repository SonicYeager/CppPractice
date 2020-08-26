#include "Video.h"

Video::Video(std::chrono::milliseconds start, std::chrono::milliseconds length, std::filesystem::path fp)
	: Clip{start, length}
	, filePath(fp)
{}

void Video::Visit(IOperations* visitor)
{
	visitor->PerformOn(this->shared_from_this()); //Visitor
}
