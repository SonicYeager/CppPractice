#include "WrappedVideoEngine.h"

void WrappedVideoEngine::Prepare(const ProjectInfo& pi)
{
	PrepareVideoEngine(pi);
}

VideoFrame* WrappedVideoEngine::GetFrame(__int64 i)
{
	return VideoEngineGetFrame(i);
}

void WrappedVideoEngine::ValidateVideoFrame(VideoFrame* videoframe)
{
	if(videoframe == nullptr)
		throw std::exception("GetFrame error");
}

inline void WrappedVideoEngine::ShutDown()
{
	ShutdownVideoEngine();
}
