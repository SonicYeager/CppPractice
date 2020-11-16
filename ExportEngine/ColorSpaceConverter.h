#pragma once
#include "Exporter.h"

class ColorSpaceConverter
{
public:
	void ConvertFrameColorFormat(IVideoExport* pExporter, VideoFrame* videoframe);
};