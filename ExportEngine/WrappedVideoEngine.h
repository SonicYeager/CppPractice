#pragma once
#include "ExportData.h"

struct WrappedVideoEngine
{
	static void Prepare(const ProjectInfo& pi);
	static VideoFrame* GetFrame(__int64 i);
	static void ValidateVideoFrame(VideoFrame* videoframe);
	static void ShutDown();
};