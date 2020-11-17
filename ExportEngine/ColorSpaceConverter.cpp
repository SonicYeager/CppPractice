#include "ColorSpaceConverter.h"
#include <functional>

void BGRToYUV(VideoFrame* videoframe)
{
	for(Pixel& c : videoframe->pixels)
	{
		Pixel bgr = c;
		c.y = static_cast<char>(0.299 * bgr.b + 0.587 * bgr.g + 0.114 * bgr.r);
		c.u = static_cast<char>((bgr.r - c.y) * 0.493);
		c.v = static_cast<char>((bgr.b - c.y) * 0.877);
	}
}

void RGBToYUV(VideoFrame* videoframe)
{
	for(Pixel& c : videoframe->pixels)
	{
		Pixel rgb = c;
		c.y = static_cast<char>(0.299 * rgb.r + 0.587 * rgb.g + 0.114 * rgb.b);
		c.u = static_cast<char>((rgb.b - c.y) * 0.493);
		c.v = static_cast<char>((rgb.r - c.y) * 0.877);
	}
}

void DetermineConversion(ExportColorFormat format, VideoFrameColorFormat colorFormat, std::function<void()> onBGR, std::function<void()> onRGB)
{
	if(static_cast<ExportColorFormat>(colorFormat) != format)
	{
		if(colorFormat == VideoFrameColorFormat::BGR and format == ExportColorFormat::YUV)
		{
			onBGR();
		}
		else if(colorFormat == VideoFrameColorFormat::RGB and format == ExportColorFormat::YUV)
		{
			onRGB();
		}
	}
}

void ConvertToYUV(VideoFrame* videoframe, ExportColorFormat format)
{
	auto onBGR = [&videoframe] { BGRToYUV(videoframe); };
	auto onRGB = [&videoframe] { RGBToYUV(videoframe); };
	DetermineConversion(format, videoframe->colorFormat, onBGR, onRGB);
}
