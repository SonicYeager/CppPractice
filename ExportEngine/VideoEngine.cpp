#include "VideoEngine.h"

__int64 start;
__int64 end;

void PrepareVideoEngine(const ProjectInfo& PI)
{
	this->mStart = PI.rangeStart;
	this->mEnd = PI.rangeEnd;
}

VideoFrame* VideoEngine::VideoEngineGetFrame(__int64 i)
{
	if(mStart > i or i > mEnd)
		return nullptr;
	char c = static_cast<char>(i);
	// clang-format off
	std::vector<Pixel> rgbData = 
	{
		{0,   0, -128}, {0,   0, -128}, {0, 0, 0}, {0, 0, 0}, {0,   0, 0}, {   0,   0,   0}, { 0,  0,  0}, {0, 0, 0}, {0, 0, 0}, {   0,   0,    0}, {0,   0, 0}, {0,   0, 0},
		{0,   0, -128}, {0,   0, -128}, {0, 0, 0}, {0, 0, 0}, {0,   0, 0}, {   0,   0,   0}, { 0,  0,  0}, {0, 0, 0}, {0, 0, 0}, {   0,   0,    0}, {0,   0, 0}, {0,   0, 0},
		{0,   0, -128}, {0,   0, -128}, {c, c, c}, {c, c, c}, {c,   c, c}, {   c,   c,   c}, { c,  c,  c}, {c, c, c}, {c, c, c}, {-116, 117, -118}, {0, 127, 0}, {0, 127, 0},
		{0,   0, -128}, {0,   0, -128}, {c, c, c}, {c, c, c}, {c,   c, c}, {   c,   c,   c}, { c,  c,  c}, {c, c, c}, {c, c, c}, {-116, 117, -118}, {0, 127, 0}, {0, 127, 0},
		{0,   0, -128}, {0,   0, -128}, {c, c, c}, {c, c, c}, {10, 50, 0}, {-100,   0, 100}, { 0, 50,-10}, {c, c, c}, {c, c, c}, { 111,  10,  112}, {0, 127, 0}, {0, 127, 0},
		{0,   0, -128}, {0,   0, -128}, {c, c, c}, {c, c, c}, {10, 50, 0}, {-100,   0, 100}, { 0, 50,-10}, {c, c, c}, {c, c, c}, {  24,  23,   22}, {0, 127, 0}, {0, 127, 0},
		{0,   0, -128}, {0,   0, -128}, {c, c, c}, {c, c, c}, {10, 50, 0}, {-100,   0, 100}, { 0, 50,-10}, {c, c, c}, {c, c, c}, {  24,  23,   22}, {0, 127, 0}, {0, 127, 0},
		{0,   0, -128}, {0,   0, -128}, {c, c, c}, {c, c, c}, {c,   c, c}, {   c,   c,   c}, { c,  c,  c}, {c, c, c}, {c, c, c}, {  24,  23,   22}, {0, 127, 0}, {0, 127, 0},
		{0,   0, -128}, {0,   0, -128}, {c, c, c}, {c, c, c}, {c,   c, c}, {   c,   c,   c}, { c,  c,  c}, {c, c, c}, {c, c, c}, {  24,  23,   22}, {0, 127, 0}, {0, 127, 0},
		{0,   0, -128}, {0,   0, -128}, {1, 2, 3}, {1, 2, 3}, {1,   2, 3}, {  88,  87,  86}, {55, 56, 52}, {1, 2, 3}, {1, 2, 3}, { 125, 126,  127}, {0, 127, 0}, {0, 127, 0},
		{127, 0,    0}, {127, 0,    0}, {127,0,0}, {127,0,0}, {127, 0, 0}, { 127,   0,   0}, {127, 0,  0}, {127,0,0}, {127,0,0}, { 127,   0,    0}, {0, 127, 0}, {0, 127, 0},
		{127, 0,    0}, {127, 0,    0}, {127,0,0}, {127,0,0}, {127, 0, 0}, { 127,   0,   0}, {127, 0,  0}, {127,0,0}, {127,0,0}, { 127,   0,    0}, {0, 127, 0}, {0, 127, 0},
	};
	// clang-format on
	return new VideoFrame{12, 12, VideoFrameColorFormat::RGB, rgbData};
}

VideoFrame* VideoEngine::GetFrame(long long i)
{
	auto res = VideoEngineGetFrame(i);
	if(res == nullptr)
		throw std::exception("GetFrame error");
	return res;
}

void VideoEngine::ShutdownVideoEngine()
{
	mStart = mEnd = 0;
}
