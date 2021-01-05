#include "ColorSpaceConverter.h"
#include <functional>

void BGRToYUV(const std::unique_ptr<VideoFrame>& videoframe)
{
	for(Pixel& c : videoframe->pixels)
	{
		Pixel bgr = c;
		c.y = static_cast<char>(0.299 * bgr.b + 0.587 * bgr.g + 0.114 * bgr.r);
		c.u = static_cast<char>((bgr.r - c.y) * 0.493);
		c.v = static_cast<char>((bgr.b - c.y) * 0.877);
	}
}

void RGBToYUV(const std::unique_ptr<VideoFrame>& videoframe)
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

void ConvertToYUV(const std::unique_ptr<VideoFrame>& videoframe, ExportColorFormat format)
{
	auto onBGR = [&videoframe] { BGRToYUV(videoframe); };
	auto onRGB = [&videoframe] { RGBToYUV(videoframe); };
	DetermineConversion(format, videoframe->colorFormat, onBGR, onRGB);
}

void BGRToGrayscale(const std::unique_ptr<VideoFrame>& videoframe)
{
	for(Pixel& c : videoframe->pixels)
	{
		Pixel rgb = c;
		auto val = (0.299 * rgb.r) + (0.587 * rgb.g) + (0.114 * rgb.b);
		c.r = static_cast<char>(val);
		c.g = static_cast<char>(val);
		c.b = static_cast<char>(val);
	}
}

void RGBToGrayscale(const std::unique_ptr<VideoFrame>& videoframe)
{
	for(Pixel& c : videoframe->pixels)
	{
		Pixel rgb = c;
		auto val = (0.299 * rgb.r) + (0.587 * rgb.g) + (0.114 * rgb.b);
		c.r = static_cast<char>(val);
		c.g = static_cast<char>(val);
		c.b = static_cast<char>(val);
	}
}

void DetermineConversion(VideoFrameColorFormat colorFormat, std::function<void()> onBGR, std::function<void()> onRGB)
{
	if(colorFormat == VideoFrameColorFormat::BGR)
	{
		onBGR();
	}
	else if(colorFormat == VideoFrameColorFormat::RGB)
	{
		onRGB();
	}
}

void ConvertToGrayscale(const std::unique_ptr<VideoFrame>& videoframe)
{	
	auto onBGR = [&videoframe] { BGRToGrayscale(videoframe); };
	auto onRGB = [&videoframe] { RGBToGrayscale(videoframe); };
	DetermineConversion(videoframe->colorFormat, onBGR, onRGB);
}
