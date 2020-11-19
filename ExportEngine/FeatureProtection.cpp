#include "FeatureProtection.h"

void ThrowIfProtectedFeature(const ExportConfig& config)
{
	if(not(config.type == ExportType::DVD or config.type == ExportType::MP4))
		throw std::exception("Feature not allowed");
}
