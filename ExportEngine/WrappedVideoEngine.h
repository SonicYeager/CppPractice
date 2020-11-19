#pragma once
#include "ExportData.h"

struct WrappedVideoEngine
{
	static void Prepare(const ProjectInfo& pi);
	static std::unique_ptr<VideoFrame> GetFrame(__int64 i);
	static void ShutDown();
};