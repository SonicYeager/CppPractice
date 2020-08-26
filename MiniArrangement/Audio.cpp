#include "Audio.h"

Audio::Audio(std::chrono::milliseconds start, std::chrono::milliseconds length, std::filesystem::path fp, int vol)
	: Clip{start, length}
	, filePath(fp)
	, volume(vol)
{}

void Audio::Visit(IOperations* visitor)
{
	visitor->PerformOn(this->shared_from_this()); //Visitor
}
