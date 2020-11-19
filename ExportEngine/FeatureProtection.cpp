#include "FeatureProtection.h"

void ThrowIfProtectedFeature(IVideoExport* pExporter, const ExportConfig& config)
{
	if(pExporter)
	{
		if(not(config.type == ExportType::DVD or config.type == ExportType::MP4))
			throw std::exception("Feature not allowed");
	}
}
