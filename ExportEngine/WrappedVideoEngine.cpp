#include "WrappedVideoEngine.h"

void WrappedVideoEngine::VideoEnginePrepare(const ProjectInfo& pi)
{
	PrepareVideoEngine(pi);
}

VideoFrame* WrappedVideoEngine::VideoEngineGetFrameT(__int64 i)
{
	return VideoEngineGetFrame(i);
}

inline void WrappedVideoEngine::VideoEngineShutDown()
{
	ShutdownVideoEngine();
}
