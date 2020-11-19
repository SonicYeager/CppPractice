#pragma once
#include "ExportData.h"

struct WrappedVideoEngine
{
	void Prepare(const ProjectInfo& pi);
	std::unique_ptr<VideoFrame> GetNextFrame();
	bool IsInRange(long long start, long long end);
	~WrappedVideoEngine();

private:
	__int64 index{};
	int framerate{};
};