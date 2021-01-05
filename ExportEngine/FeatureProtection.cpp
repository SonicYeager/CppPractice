#include "FeatureProtection.h"

void ThrowIfProtectedFeature(const ExportType& type)
{
	if(not(type == ExportType::DVD or type == ExportType::MP4))
		throw std::exception("Feature not allowed");
}
