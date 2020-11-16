#pragma once
#include <vector>
#include "ArrangmentData.h"

enum class VideoFrameColorFormat
{
	RGB = 0,
	BGR
};

struct Pixel
{
	union
	{
		struct
		{
			char y, u, v;
		};
		struct
		{
			char r, g, b;
		};
	};
};

struct VideoFrame
{
	int width = 5;
	int height = 5;
	VideoFrameColorFormat colorFormat = VideoFrameColorFormat::RGB;
	std::vector<Pixel> pixels = {};
};

struct VideoEngine
{
	void PrepareVideoEngine(const ProjectInfo&);
	VideoFrame* VideoEngineGetFrame(__int64 i);
	VideoFrame* GetFrame(long long i);
	void ShutdownVideoEngine();

private:
	__int64 mStart = 0;
	__int64 mEnd = 0;
};

