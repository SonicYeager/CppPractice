#include "WrappedVideoEngine.h"

void WrappedVideoEngine::Prepare(const ProjectInfo& pi)
{
	PrepareVideoEngine(pi);
}

VideoFrame* WrappedVideoEngine::GetFrame(__int64 i)
{
	return VideoEngineGetFrame(i);
}

inline void WrappedVideoEngine::ShutDown()
{
	ShutdownVideoEngine();
}
