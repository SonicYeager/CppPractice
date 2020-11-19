#include "ExporterConfig.h"

std::unique_ptr<IVideoExport> ConfigExporter(IVideoExport* pExporter, std::function<IVideoExport*(ExportColorFormat)> create, ExportFlags flags)
{
	if(pExporter)
	{
		std::unique_ptr<IVideoExport> exp{pExporter};
		return std::move(exp);
	}
	else
	{
		if(create)
		{
			std::unique_ptr<IVideoExport> exp{std::move(create(flags & RGB_EXPORT ? ExportColorFormat::RGB : ExportColorFormat::YUV))};
			return std::move(exp);
		}
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
