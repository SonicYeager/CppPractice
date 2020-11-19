#include "WrappedVideoEngine.h"

void WrappedVideoEngine::Prepare(const ProjectInfo& pi)
{
	PrepareVideoEngine(pi);
}

std::unique_ptr<VideoFrame> WrappedVideoEngine::GetFrame(__int64 i)
{
	std::unique_ptr<VideoFrame> videoframe{VideoEngineGetFrame(i)};
	if(videoframe == nullptr)
		throw std::exception("GetFrame error");

	return videoframe;
}


void WrappedVideoEngine::ShutDown()
{
	ShutdownVideoEngine();
}
