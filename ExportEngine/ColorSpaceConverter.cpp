#include "ColorSpaceConverter.h"

void ConvertToYUV(VideoFrame* videoframe, ExportColorFormat format)
{
	if(static_cast<ExportColorFormat>(videoframe->colorFormat) != format)
	{
		if(videoframe->colorFormat == VideoFrameColorFormat::BGR and format == ExportColorFormat::YUV)
		{
			for(Pixel& c : videoframe->pixels)
			{
				Pixel bgr = c;
				c.y = static_cast<char>(0.299 * bgr.b + 0.587 * bgr.g + 0.114 * bgr.r);
				c.u = static_cast<char>((bgr.r - c.y) * 0.493);
				c.v = static_cast<char>((bgr.b - c.y) * 0.877);
			}
		}
		else if(videoframe->colorFormat == VideoFrameColorFormat::RGB and format == ExportColorFormat::YUV)
		{
			for(Pixel& c : videoframe->pixels)
			{
				Pixel rgb = c;
				c.y = static_cast<char>(0.299 * rgb.r + 0.587 * rgb.g + 0.114 * rgb.b);
				c.u = static_cast<char>((rgb.b - c.y) * 0.493);
				c.v = static_cast<char>((rgb.r - c.y) * 0.877);
			}
		}
	}
}
