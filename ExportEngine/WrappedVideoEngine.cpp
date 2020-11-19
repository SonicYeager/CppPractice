#include "WrappedVideoEngine.h"

void WrappedVideoEngine::Prepare(const ProjectInfo& pi)
{
	PrepareVideoEngine(pi);
	index = pi.rangeStart;
	framerate = pi.frameRate;
}

std::unique_ptr<VideoFrame> WrappedVideoEngine::GetNextFrame()
{
	std::unique_ptr<VideoFrame> videoframe{VideoEngineGetFrame(index)};
	if(videoframe == nullptr)
		throw std::exception("GetFrame error");
	index += static_cast<__int64>(framerate);
	return videoframe;
}


WrappedVideoEngine::~WrappedVideoEngine()
{
	ShutdownVideoEngine();
}
