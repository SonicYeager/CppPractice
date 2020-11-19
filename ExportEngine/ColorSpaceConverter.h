#pragma once
#include "ExportData.h"

void ConvertToYUV(const std::unique_ptr<VideoFrame>& videoframe, ExportColorFormat format);