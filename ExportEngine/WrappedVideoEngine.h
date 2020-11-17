#pragma once
#include "ExportData.h"

struct WrappedVideoEngine
{
	static void VideoEnginePrepare(const ProjectInfo& pi);
	static VideoFrame* VideoEngineGetFrameT(__int64 i);
	static void VideoEngineShutDown();
};