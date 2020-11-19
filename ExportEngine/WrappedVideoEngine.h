#pragma once
#include "ExportData.h"

struct WrappedVideoEngine
{
	void Prepare(const ProjectInfo& pi);
	std::unique_ptr<VideoFrame> GetNextFrame();
	~WrappedVideoEngine();

private:
	__int64 index{};
	int framerate{};
};