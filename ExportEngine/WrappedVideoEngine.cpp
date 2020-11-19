#include "WrappedVideoEngine.h"

void WrappedVideoEngine::Prepare(const ProjectInfo& pi)
{
	PrepareVideoEngine(pi);
}

std::unique_ptr<VideoFrame> WrappedVideoEngine::GetFrame(__int64 i)
{
	std::unique_ptr<VideoFrame> videoframe{std::move(VideoEngineGetFrame(i))};
	if(videoframe == nullptr)
		throw std::exception("GetFrame error");

	return std::move(videoframe);
}


void WrappedVideoEngine::ShutDown()
{
	ShutdownVideoEngine();
}
