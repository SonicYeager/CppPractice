#include "ExporterConfig.h"

IVideoExport* ConfigExporter(IVideoExport* pExporter, std::function<IVideoExport*(ExportColorFormat)> create, ExportFlags flags)
{
	if(pExporter)
	{
		return pExporter;
	}
	else
	{
		if(create)
			return std::move(create(flags & RGB_EXPORT ? ExportColorFormat::RGB : ExportColorFormat::YUV));
		else
			throw std::exception("no export available");
	}
}

ExportConfig GetExportConfig(IVideoExport* pExporter)
{
	ExportConfig config{};
	pExporter->GetExportInfo(&config);
	return config;
}
