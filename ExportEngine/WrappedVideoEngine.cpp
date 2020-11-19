#include "WrappedVideoEngine.h"

void WrappedVideoEngine::Prepare(const ProjectInfo& pi)
{
	PrepareVideoEngine(pi);
}

void ValidateVideoFrame(VideoFrame* videoframe)
{
	if(videoframe == nullptr)
		throw std::exception("GetFrame error");
}

VideoFrame* WrappedVideoEngine::GetFrame(__int64 i)
{
	auto videoframe = VideoEngineGetFrame(i);
	ValidateVideoFrame(videoframe);
	return std::move(videoframe);
}


void WrappedVideoEngine::ShutDown()
{
	ShutdownVideoEngine();
}
